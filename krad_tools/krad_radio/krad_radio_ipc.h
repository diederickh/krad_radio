#define EBML_ID_KRAD_RADIO_CMD 0x7384
#define EBML_ID_KRAD_MIXER_CMD 0x73A4
#define EBML_ID_KRAD_COMPOSITOR_CMD 0x73C4
#define EBML_ID_KRAD_LINK_CMD 0x73C5

#define EBML_ID_KRAD_RADIO_MSG 0x437C
#define EBML_ID_KRAD_MIXER_MSG 0x450D
#define EBML_ID_KRAD_LINK_MSG 0x6911
#define EBML_ID_KRAD_COMPOSITOR_MSG 0x53B8

#define EBML_ID_KRAD_RADIO_CMD_OSC_ENABLE 0x467E
#define EBML_ID_KRAD_RADIO_CMD_OSC_DISABLE 0x61A7

#define EBML_ID_KRAD_RADIO_CMD_WEB_ENABLE 0xCE
#define EBML_ID_KRAD_RADIO_CMD_WEB_DISABLE 0xCD

#define EBML_ID_KRAD_RADIO_CMD_REMOTE_ENABLE 0x80
#define EBML_ID_KRAD_RADIO_CMD_REMOTE_DISABLE 0x89

#define EBML_ID_KRAD_RADIO_CMD_SET_TAG 0xAE
#define EBML_ID_KRAD_RADIO_CMD_GET_TAG 0xD7
#define EBML_ID_KRAD_RADIO_CMD_LIST_TAGS 0xB9

#define EBML_ID_KRAD_RADIO_CMD_UPTIME 0xA6
#define EBML_ID_KRAD_RADIO_CMD_INFO 0xA5

#define EBML_ID_KRAD_RADIO_UPTIME 0xFB
#define EBML_ID_KRAD_RADIO_INFO 0xFD

#define EBML_ID_KRAD_RADIO_HTTP_PORT 0xCA
#define EBML_ID_KRAD_RADIO_WEBSOCKET_PORT 0xCB
#define EBML_ID_KRAD_RADIO_TCP_PORT 0x8F
#define EBML_ID_KRAD_RADIO_UDP_PORT 0x535F


#define EBML_ID_KRAD_RADIO_TAG_LIST 0x9C
#define EBML_ID_KRAD_RADIO_TAG 0x88
#define EBML_ID_KRAD_RADIO_TAG_ITEM 0x63C0
#define EBML_ID_KRAD_RADIO_TAG_NAME 0x45A3
#define EBML_ID_KRAD_RADIO_TAG_VALUE 0x4487
#define EBML_ID_KRAD_RADIO_TAG_SOURCE 0x63C9 // triplets? S4 future? oh my!

#define EBML_ID_KRAD_COMPOSITOR_CMD_SET_BUG 0x46AE
#define EBML_ID_KRAD_COMPOSITOR_FILENAME 0x466E

#define EBML_ID_KRAD_COMPOSITOR_CMD_HEX_DEMO 0x6624
#define EBML_ID_KRAD_COMPOSITOR_X 0x66FC
#define EBML_ID_KRAD_COMPOSITOR_Y 0x66BF
#define EBML_ID_KRAD_COMPOSITOR_SIZE 0x66A5

#define EBML_ID_KRAD_COMPOSITOR_CMD_VU_MODE 0x437E
#define EBML_ID_KRAD_COMPOSITOR_VU_ON 0x6944

#define EBML_ID_KRAD_MIXER_PORTGROUP_CREATED 0xE0 // Broadcast
#define EBML_ID_KRAD_MIXER_PORTGROUP_DESTROYED 0xAA // Broadcast
#define EBML_ID_KRAD_MIXER_PORTGROUP_UPDATED 0xFA // Broadcast

#define EBML_ID_KRAD_MIXER_CMD_LIST_PORTGROUPS 0xB0
#define EBML_ID_KRAD_MIXER_CMD_CREATE_PORTGROUP 0xEA
#define EBML_ID_KRAD_MIXER_CMD_UPDATE_PORTGROUP 0x9B
#define EBML_ID_KRAD_MIXER_CMD_DESTROY_PORTGROUP 0xDB
#define EBML_ID_KRAD_MIXER_CMD_PUSH_TONE 0x54AA
#define EBML_ID_KRAD_MIXER_TONE_NAME 0x54BB
#define EBML_ID_KRAD_MIXER_PORTGROUP_LIST 0xBA
#define EBML_ID_KRAD_MIXER_PORTGROUP 0xE1

#define EBML_ID_KRAD_MIXER_PORTGROUP_NAME 0xE2
#define EBML_ID_KRAD_MIXER_PORTGROUP_CHANNELS 0xE3
#define EBML_ID_KRAD_MIXER_PORTGROUP_DIRECTION 0xAF
#define EBML_ID_KRAD_MIXER_PORTGROUP_TYPE 0xE4
#define EBML_ID_KRAD_MIXER_PORTGROUP_VOLUME 0xE5
#define EBML_ID_KRAD_MIXER_PORTGROUP_MIXBUS 0xE6

#define EBML_ID_KRAD_MIXER_PORTGROUP_CROSSFADE_NAME 0xA3
#define EBML_ID_KRAD_MIXER_PORTGROUP_CROSSFADE 0xE7 // the value itself

#define EBML_ID_KRAD_MIXER_CMD_SET_CONTROL 0xA7
#define EBML_ID_KRAD_MIXER_CMD_GET_CONTROL 0xAB
#define EBML_ID_KRAD_MIXER_CONTROL 0xA1


#define EBML_ID_KRAD_MIXER_CONTROL_NAME 0xF7
#define EBML_ID_KRAD_MIXER_CONTROL_VALUE 0xF1


#define EBML_ID_KRAD_LINK_CMD_LIST_LINKS 0xB7
#define EBML_ID_KRAD_LINK_CMD_CREATE_LINK 0xED
#define EBML_ID_KRAD_LINK_CMD_DESTROY_LINK 0xE9
#define EBML_ID_KRAD_LINK_CMD_UPDATE_LINK 0xB3

#define EBML_ID_KRAD_LINK_LINK_NUMBER 0xB5



#define EBML_ID_KRAD_LINK_LINK_LIST 0xC0

#define EBML_ID_KRAD_LINK_LINK 0xC1
#define EBML_ID_KRAD_LINK_LINK_OPERATION_MODE 0xC2
#define EBML_ID_KRAD_LINK_LINK_TRANSPORT_MODE 0xC3
#define EBML_ID_KRAD_LINK_LINK_AV_MODE 0xC4

#define EBML_ID_KRAD_LINK_LINK_VIDEO_SOURCE 0x3CB923

#define EBML_ID_KRAD_LINK_LINK_AUDIO_CODEC 0x91
#define EBML_ID_KRAD_LINK_LINK_VIDEO_CODEC 0x92

#define EBML_ID_KRAD_LINK_LINK_OGG_MAX_PACKETS_PER_PAGE 0x26B240

#define EBML_ID_KRAD_LINK_LINK_OPUS_APPLICATION 0x23E383
#define EBML_ID_KRAD_LINK_LINK_OPUS_BITRATE 0x23314F
#define EBML_ID_KRAD_LINK_LINK_OPUS_SIGNAL 0x22B59C
#define EBML_ID_KRAD_LINK_LINK_OPUS_BANDWIDTH 0x4598
#define EBML_ID_KRAD_LINK_LINK_OPUS_COMPLEXITY 0x55EE
#define EBML_ID_KRAD_LINK_LINK_OPUS_FRAME_SIZE 0x536E

#define EBML_ID_KRAD_LINK_LINK_FILENAME 0xC5

#define EBML_ID_KRAD_LINK_LINK_HOST 0xC6
#define EBML_ID_KRAD_LINK_LINK_PORT 0xC7
#define EBML_ID_KRAD_LINK_LINK_MOUNT 0xC8
#define EBML_ID_KRAD_LINK_LINK_PASSWORD 0xC9

#define EBML_ID_KRAD_LINK_LINK_VP8_FORCE_KEYFRAME 0x6933
#define EBML_ID_KRAD_LINK_LINK_VP8_BITRATE 0x6922
#define EBML_ID_KRAD_LINK_LINK_VIDEO_WIDTH 0x54B0
#define EBML_ID_KRAD_LINK_LINK_VIDEO_HEIGHT 0x54BA


//54BA 54B3 54CC 54DD

