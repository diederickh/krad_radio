#ifndef __CAPTURE_H__
#define __CAPTURE_H__

typedef struct krad_decklink_capture_St krad_decklink_capture_t;

#ifdef __cplusplus

#include "DeckLinkAPI.h"
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

class DeckLinkCaptureDelegate : public IDeckLinkInputCallback
{
public:
	DeckLinkCaptureDelegate();
	~DeckLinkCaptureDelegate();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv) { return E_NOINTERFACE; }
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE  Release(void);
	virtual HRESULT STDMETHODCALLTYPE VideoInputFormatChanged(BMDVideoInputFormatChangedEvents, IDeckLinkDisplayMode*, BMDDetectedVideoInputFormatFlags);
	virtual HRESULT STDMETHODCALLTYPE VideoInputFrameArrived(IDeckLinkVideoInputFrame*, IDeckLinkAudioInputPacket*);

	krad_decklink_capture_t *krad_decklink_capture;

private:
	ULONG				m_refCount;
	pthread_mutex_t		m_mutex;
};

#ifndef KRAD_DECKLINK_H
struct krad_decklink_capture_St {

	IDeckLink *deckLink;
	IDeckLinkInput *deckLinkInput;
	IDeckLinkIterator *deckLinkIterator;
	IDeckLinkDisplayModeIterator *displayModeIterator;
	IDeckLinkDisplayMode *displayMode;
	int inputFlags;
	DeckLinkCaptureDelegate *delegate;
	HRESULT result;
	
	int verbose;

	int skip_frame;
	int skip_frames;
	
	BMDDisplayMode display_mode;
	BMDPixelFormat pixel_format;
	BMDAudioSampleRate audio_sample_rate; 
	int audio_channels;
	int audio_bit_depth;
	
	uint64_t video_frames;
	uint64_t audio_frames;
	
	int (*video_frame_callback)(void *, void *, int);
	int (*audio_frames_callback)(void *, void *, int);
	void *callback_pointer;

};
#endif


extern "C" {
#endif

krad_decklink_capture_t *krad_decklink_capture_create();
void krad_decklink_capture_start(krad_decklink_capture_t *krad_decklink_capture);
void krad_decklink_capture_stop(krad_decklink_capture_t *krad_decklink_capture);
void krad_decklink_capture_info ();

void krad_decklink_capture_set_verbose(krad_decklink_capture_t *krad_decklink_capture, int verbose);
void krad_decklink_capture_set_video_callback(krad_decklink_capture_t *krad_decklink_capture, int video_frame_callback(void *, void *, int));
void krad_decklink_capture_set_audio_callback(krad_decklink_capture_t *krad_decklink_capture, int audio_frames_callback(void *, void *, int));
void krad_decklink_capture_set_callback_pointer(krad_decklink_capture_t *krad_decklink_capture, void *callback_pointer);

#ifdef __cplusplus
}

#endif

#endif
