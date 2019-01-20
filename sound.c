/*-------------------------------------------------------
  Instituto Superior Técnico - 1st Semester 18/19

  Integrated Avionic Systems


  	FILE sound.c
  	"Contains the functions related to sound"
	
	IMPORTANT: The sounds used do not belong to us! 
	They are freeware and can be found in:
	https://www.youtube.com/watch?v=xYit3zKbZkw Inner Marker
	https://www.youtube.com/watch?v=sSdlsB5NSsw Middle Marker
	https://www.youtube.com/watch?v=AW8IF9WdoD0 Outer Marker
	
	NOTE: need to install vlc library:
	sudo apt-get install libvlccore-dev libvlc-dev


  Authors:
    Francisco Castro, 78655
    Diogo Dores, 
    Pedro Angélico, 

  Date: 
    23-01-2019
---------------------------------------------------------*/
#include "general.h"

/*
    Function: sound
    Handles the sound alerts thread
*/
void *sound(void *vargp, ILS status)
{
    libvlc_instance_t *inst;
    libvlc_media_player_t *mp;
    libvlc_media_t *m;

    char alert_sound[STATUS_SIZE] = "";
    int mb = 0;

    // run until program closed
    while (exiting == 0) {

        // load the engine
        inst = libvlc_new(0, NULL);

        if (status.mb.im == 0 && status.mb.om == 0 && status.mb.mm == 0)
        	mb = 0; //alerts won't be played;
        else {
            // MM on
            if (status.mb.om == 1)
                strcpy(alert_sound, "Outer VHF Marker Beacon.wav");
            // OM on
            else if (status.mb.mm == 1)
                strcpy(alert_sound, "Middle VHF Marker Beacon.wav");
            // IM on
            else if (status.mb.im == 1)
                strcpy(alert_sound, "Inner VHF Marker.wav");
        }

        // create a file to play
        m = libvlc_media_new_path(inst, alert_sound);

        // create a media play playing environment
        mp = libvlc_media_player_new_from_media(m);

        // release the media now.
        libvlc_media_release(m);

        // play the media_player
        libvlc_media_player_play(mp);

        // play for 3 seconds
        sleep(5);

        // stop playing
        libvlc_media_player_stop(mp);

        libvlc_media_player_release(mp);
        libvlc_release(inst);
    }

    return NULL;
}
