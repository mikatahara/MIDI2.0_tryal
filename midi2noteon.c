/*
    midi2noteon.c --- Copyright (c) 2024 Mikata Hara
    This software is released under the MIT License, see LICENSE.txt.
    ver0.01 12/30/2024

    Send UMP MT4 Note ON and OFF messages 100 times at 250 ms intervals.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <poll.h>
#include <stdbool.h>
#include <alsa/asoundlib.h>
#include <alsa/ump_msg.h>
            
static snd_seq_t *seq_handle;
static int port_out;
static int client=20;
static int port=0;
            
int main(int argc, char *argv[])
{
    /* open sequencer */
    int err = snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_DUPLEX, 0);
    if(err<0){ fprintf(stderr,"open sequencer error\n"); exit(EOF); }
            
    /* set our client's name */
    err = snd_seq_set_client_name(seq_handle, "midi2send");
    if(err<0){ fprintf(stderr,"set client name error\n"); exit(EOF); }
            
    /* create port */
    port_out = snd_seq_create_simple_port(seq_handle, "Output",
        SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
        SND_SEQ_PORT_TYPE_APPLICATION);
    if(port_out<0){ fprintf(stderr,"set client name error\n"); exit(EOF); }
                    
    // set client midi version;
    snd_seq_set_client_midi_version(seq_handle,SND_SEQ_CLIENT_UMP_MIDI_2_0);
            
    // connect port
    err = snd_seq_connect_to(seq_handle, 0, client, port);
    if(err<0){ fprintf(stderr,"connect port error\n"); exit(EOF); }
                
    // Event preparetion
    snd_seq_ump_event_t event;
    memset((char*)&event,0,sizeof(snd_seq_ump_event_t));
            
    snd_seq_ev_set_source(&event, port_out);
    snd_seq_ev_set_subs(&event);
    snd_seq_ev_set_direct(&event);
    event.flags = event.flags|SND_SEQ_EVENT_UMP;
    event.type = SND_UMP_MSG_TYPE_MIDI2_CHANNEL_VOICE;
            
    snd_ump_msg_midi2_t *m = (snd_ump_msg_midi2_t *)&event.ump;
    m->hdr.type=SND_UMP_MSG_TYPE_MIDI2_CHANNEL_VOICE;
    m->hdr.group=0;
    m->hdr.channel=0;
            
            
    for(int j=0; j<100; j++){
            
        // Note On
        m->hdr.status=SND_UMP_MSG_NOTE_ON;
        m->note_on.note =0x10+j,
        m->note_on.velocity = 0xC000 + (uint16_t)((float)j/100*0x200);
        m->note_on.attr_type = 0x11;
        m->note_on.attr_data = 0x2345;
            printf("*** %04x\n",m->note_on.velocity);
            
        int err=snd_seq_ump_event_output(seq_handle,&event);
        if(err<0){
            fprintf(stderr, "Failed to send event. %d\n",err);
            snd_seq_close(seq_handle);
            return (EOF);
        }
            
        err=snd_seq_drain_output(seq_handle);
        if(err<0){
            fprintf(stderr, "Failed to drain. %d\n",err);
            snd_seq_close(seq_handle);
            return (EOF);
        }
            
        usleep(250000);
            
        // Note Off
        m->hdr.status=SND_UMP_MSG_NOTE_OFF;
        m->note_off.note =0x10+j,
        m->note_off.velocity = 0x2000 + (uint16_t)((float)j/100*0x200);
        m->note_off.attr_type = 0x11;
        m->note_off.attr_data = 0x2345;
        printf("*** %04x\n",m->note_on.velocity);
            
        err=snd_seq_ump_event_output(seq_handle,&event);
        if(err<0){
            fprintf(stderr, "Failed to send event. %d\n",err);
            snd_seq_close(seq_handle);
            return 1;
        }
            
        err=snd_seq_drain_output(seq_handle);
        if(err<0){
            fprintf(stderr, "Failed to drain. %d\n",err);
            snd_seq_close(seq_handle);
            return 1;
        }
            
        usleep(250000);
    }
            
    // Close sequencer
    snd_seq_close(seq_handle);
    return 0;
}

