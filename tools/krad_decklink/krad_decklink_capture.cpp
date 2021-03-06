#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#include "DeckLinkAPI.h"

#include "krad_decklink_capture.h"



DeckLinkCaptureDelegate::DeckLinkCaptureDelegate() : m_refCount(0)
{
	pthread_mutex_init(&m_mutex, NULL);
}

DeckLinkCaptureDelegate::~DeckLinkCaptureDelegate()
{
	pthread_mutex_destroy(&m_mutex);
}

ULONG DeckLinkCaptureDelegate::AddRef(void)
{
	pthread_mutex_lock(&m_mutex);
		m_refCount++;
	pthread_mutex_unlock(&m_mutex);

	return (ULONG)m_refCount;
}

ULONG DeckLinkCaptureDelegate::Release(void)
{
	pthread_mutex_lock(&m_mutex);
		m_refCount--;
	pthread_mutex_unlock(&m_mutex);

	if (m_refCount == 0)
	{
		delete this;
		return 0;
	}

	return (ULONG)m_refCount;
}

HRESULT DeckLinkCaptureDelegate::VideoInputFrameArrived(IDeckLinkVideoInputFrame* video_frame, IDeckLinkAudioInputPacket* audio_frame) {

	void *frame_data;
	long int frame_data_size;
	void *audio_data;
	const char *timecodeString;
	IDeckLinkTimecode *timecode;
	BMDTimecodeFormat timecodeFormat;
	int audio_frames;
	
	timecodeString = NULL;
	timecodeFormat = 0;
	frame_data_size = 0;
	

	if (audio_frame) {
		audio_frame->GetBytes(&audio_data);
		audio_frames = audio_frame->GetSampleFrameCount();
		if (krad_decklink_capture->verbose) {
		//	printf("Audio Frame received %d frames\r", audio_frames);
		}
		if (krad_decklink_capture->audio_frames_callback != NULL) {
			krad_decklink_capture->audio_frames_callback (krad_decklink_capture->callback_pointer, audio_data, audio_frames);
		}		
		krad_decklink_capture->audio_frames += audio_frames;
	}	
	
	
	if (krad_decklink_capture->skip_frame == 1) {
		krad_decklink_capture->skip_frame = 0;
	    return S_OK;
	}
	
	if (krad_decklink_capture->skip_frame == 0) {
		krad_decklink_capture->skip_frame = 1;
	}	
	
	if (video_frame) {

		if (video_frame->GetFlags() & bmdFrameHasNoInputSource) {
		//	printf("Frame received (#%"PRIu64") - No input signal detected\n", krad_decklink_capture->video_frames);
		} else {

			if (timecodeFormat != 0) {
				if (video_frame->GetTimecode(timecodeFormat, &timecode) == S_OK) {
					timecode->GetString(&timecodeString);
				}
			}
			
			frame_data_size = video_frame->GetRowBytes() * video_frame->GetHeight();

			//if (krad_decklink_capture->verbose) {
			//	printf("Frame received (#%"PRIu64") [%s] - Size: %li bytes ", 
			//			krad_decklink_capture->video_frames, 
			//			timecodeString != NULL ? timecodeString : "No timecode",
			//			frame_data_size);
			//}
			
			if (timecodeString) {
				free ((void*)timecodeString);
			}
			
			video_frame->GetBytes(&frame_data);

			if (krad_decklink_capture->video_frame_callback != NULL) {
				krad_decklink_capture->video_frame_callback (krad_decklink_capture->callback_pointer, frame_data, frame_data_size);
			}
			
		}
		
		krad_decklink_capture->video_frames++;
		
	}
	
	if (krad_decklink_capture->verbose) {
		fflush(stdout);
	}
    return S_OK;
}

HRESULT DeckLinkCaptureDelegate::VideoInputFormatChanged(BMDVideoInputFormatChangedEvents events, IDeckLinkDisplayMode *mode, BMDDetectedVideoInputFormatFlags) {

	//printf("ruh oh! video format changed?!?\n");

    return S_OK;
}

extern "C" {

krad_decklink_capture_t *krad_decklink_capture_create() {

	krad_decklink_capture_t *krad_decklink_capture = (krad_decklink_capture_t *)calloc(1, sizeof(krad_decklink_capture_t));
	
	
	krad_decklink_capture->pixel_format = bmdFormat8BitYUV;
	//krad_decklink_capture->pixel_format = bmdFormat8BitARGB;
	krad_decklink_capture->display_mode = bmdModeHD720p5994;
	krad_decklink_capture->display_mode = bmdModeHD720p60;
	krad_decklink_capture->inputFlags = 0;
	
	krad_decklink_capture->audio_sample_rate = bmdAudioSampleRate48kHz;
	krad_decklink_capture->audio_channels = 2;
	krad_decklink_capture->audio_bit_depth = 16;
	
	krad_decklink_capture->deckLinkIterator = CreateDeckLinkIteratorInstance();
	
	if (!krad_decklink_capture->deckLinkIterator) {
		//printf("Krad Decklink: This application requires the DeckLink drivers installed.\n");
		return 0;
	}
	
	/* Connect to the first DeckLink instance */
	krad_decklink_capture->result = krad_decklink_capture->deckLinkIterator->Next(&krad_decklink_capture->deckLink);
	if (krad_decklink_capture->result != S_OK) {
		//printf("Krad Decklink: No DeckLink PCI cards found.\n");
	}

	return krad_decklink_capture;
	
}

void krad_decklink_capture_set_video_callback(krad_decklink_capture_t *krad_decklink_capture, int video_frame_callback(void *, void *, int)) {
	krad_decklink_capture->video_frame_callback = video_frame_callback;
}

void krad_decklink_capture_set_audio_callback(krad_decklink_capture_t *krad_decklink_capture, int audio_frames_callback(void *, void *, int)) {
	krad_decklink_capture->audio_frames_callback = audio_frames_callback;
}

void krad_decklink_capture_set_callback_pointer(krad_decklink_capture_t *krad_decklink_capture, void *callback_pointer) {
	krad_decklink_capture->callback_pointer = callback_pointer;
}

void krad_decklink_capture_set_verbose(krad_decklink_capture_t *krad_decklink_capture, int verbose) {
	krad_decklink_capture->verbose = verbose;
}

void krad_decklink_capture_start(krad_decklink_capture_t *krad_decklink_capture) {
    
	krad_decklink_capture->result = krad_decklink_capture->deckLink->QueryInterface(IID_IDeckLinkInput, (void**)&krad_decklink_capture->deckLinkInput);
	if (krad_decklink_capture->result != S_OK) {
		//printf("Krad Decklink: Fail QueryInterface\n");
	}

	krad_decklink_capture->delegate = new DeckLinkCaptureDelegate();
	krad_decklink_capture->delegate->krad_decklink_capture = krad_decklink_capture;
	krad_decklink_capture->deckLinkInput->SetCallback(krad_decklink_capture->delegate);

	krad_decklink_capture->result = krad_decklink_capture->deckLinkInput->EnableVideoInput(krad_decklink_capture->display_mode, krad_decklink_capture->pixel_format, krad_decklink_capture->inputFlags);
	if (krad_decklink_capture->result != S_OK) {
		//printf("Krad Decklink: Fail EnableVideoInput\n");
	}

	krad_decklink_capture->result = krad_decklink_capture->deckLinkInput->EnableAudioInput(krad_decklink_capture->audio_sample_rate, krad_decklink_capture->audio_bit_depth, krad_decklink_capture->audio_channels);
	if (krad_decklink_capture->result != S_OK) {
		//printf("Krad Decklink: Fail EnableAudioInput\n");
	}

	krad_decklink_capture->result = krad_decklink_capture->deckLinkInput->StartStreams();
	if (krad_decklink_capture->result != S_OK) {
		//printf("Krad Decklink: Fail StartStreams\n");
	}
	
	//printf("\n");

}

void krad_decklink_capture_stop(krad_decklink_capture_t *krad_decklink_capture) {

    if (krad_decklink_capture->deckLinkInput != NULL) {
    
		krad_decklink_capture->result = krad_decklink_capture->deckLinkInput->StopStreams ();
		if (krad_decklink_capture->result != S_OK) {
			//printf("Krad Decklink: Fail StopStreams\n");
		}		
		krad_decklink_capture->result = krad_decklink_capture->deckLinkInput->DisableVideoInput ();
		if (krad_decklink_capture->result != S_OK) {
			//printf("Krad Decklink: Fail DisableVideoInput\n");
		}
		krad_decklink_capture->result = krad_decklink_capture->deckLinkInput->DisableAudioInput ();
		if (krad_decklink_capture->result != S_OK) {
			//printf("Krad Decklink: Fail DisableAudioInput\n");
		}
		krad_decklink_capture->result = krad_decklink_capture->deckLinkInput->Release();
		if (krad_decklink_capture->result != S_OK) {
			//printf("Krad Decklink: Fail Release\n");
		}
        krad_decklink_capture->deckLinkInput = NULL;
    }

    if (krad_decklink_capture->deckLink != NULL) {
        krad_decklink_capture->deckLink->Release();
        krad_decklink_capture->deckLink = NULL;
    }

	if (krad_decklink_capture->deckLinkIterator != NULL) {
		krad_decklink_capture->deckLinkIterator->Release();
	}
	
	//printf("\n");

	free(krad_decklink_capture);

}

void krad_decklink_capture_info () {

	IDeckLink *deckLink;
	IDeckLinkInput *deckLinkInput;
	IDeckLinkIterator *deckLinkIterator;
	IDeckLinkDisplayModeIterator *displayModeIterator;
	IDeckLinkDisplayMode *displayMode;
	
	HRESULT result;
	int displayModeCount;
	char *displayModeString;

	displayModeString = NULL;
	displayModeCount = 0;
	
	deckLinkIterator = CreateDeckLinkIteratorInstance();
	
	if (!deckLinkIterator) {
		//printf("Krad Decklink: This application requires the DeckLink drivers installed.\n");
	}
	
	/* Connect to the first DeckLink instance */
	result = deckLinkIterator->Next(&deckLink);
	if (result != S_OK) {
		//printf("Krad Decklink: No DeckLink PCI cards found.\n");
	}
    
	result = deckLink->QueryInterface(IID_IDeckLinkInput, (void**)&deckLinkInput);
	if (result != S_OK) {
		//printf("Krad Decklink: Fail QueryInterface\n");
	}
	
	result = deckLinkInput->GetDisplayModeIterator(&displayModeIterator);
	if (result != S_OK) {
		//printf("Krad Decklink: Could not obtain the video output display mode iterator - result = %08x\n", result);
	}


    while (displayModeIterator->Next(&displayMode) == S_OK) {

        result = displayMode->GetName((const char **) &displayModeString);
        
        if (result == S_OK) {
			
			BMDTimeValue frameRateDuration, frameRateScale;
			displayMode->GetFrameRate(&frameRateDuration, &frameRateScale);

			//printf("%2d:  %-20s \t %li x %li \t %g FPS\n", 
			//	displayModeCount, displayModeString, displayMode->GetWidth(), displayMode->GetHeight(), 
			//	(double)frameRateScale / (double)frameRateDuration);
			
            free (displayModeString);
			displayModeCount++;
		}
		
		displayMode->Release();
	}
	
	if (displayModeIterator != NULL) {
		displayModeIterator->Release();
		displayModeIterator = NULL;
	}

    if (deckLinkInput != NULL) {
        deckLinkInput->Release();
        deckLinkInput = NULL;
    }

    if (deckLink != NULL) {
        deckLink->Release();
        deckLink = NULL;
    }

	if (deckLinkIterator != NULL) {
		deckLinkIterator->Release();
	}
}

}

	

