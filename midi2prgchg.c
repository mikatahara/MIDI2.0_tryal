/*
    midi2prgchg.c --- Copyright (c) 2024 Mikata Hara
    This software is released under the MIT License, see LICENSE.txt.
    ver0.01 3/23/2026

    Send UMP MT4 Program Change message.
    Enter three numbers, LSB/MSB.PC. Each number must be between 0 and 127.
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
static int client = 20;
static int port = 0;

int main(int argc, char *argv[])
{
    uint8_t lsb, msb, pc;
    char str[256];

    /* open sequencer */
    int err = snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_DUPLEX, 0);
    if (err < 0)
    {
        fprintf(stderr, "open sequencer error\n");
        exit(EOF);
    }

    /* set our client's name */
    err = snd_seq_set_client_name(seq_handle, "midi2send");
    if (err < 0)
    {
        fprintf(stderr, "set client name error\n");
        exit(EOF);
    }

    /* create port */
    port_out = snd_seq_create_simple_port(seq_handle, "Output",
                                          SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
                                          SND_SEQ_PORT_TYPE_APPLICATION);
    if (port_out < 0)
    {
        fprintf(stderr, "set client name error\n");
        exit(EOF);
    }

    // set client midi version;
    snd_seq_set_client_midi_version(seq_handle, SND_SEQ_CLIENT_UMP_MIDI_2_0);

    // connect port
    err = snd_seq_connect_to(seq_handle, 0, client, port);
    if (err < 0)
    {
        fprintf(stderr, "connect port error\n");
        exit(EOF);
    }

    // Event preparetion
    snd_seq_ump_event_t event;
    memset((char *)&event, 0, sizeof(snd_seq_ump_event_t));

    snd_seq_ev_set_source(&event, port_out);
    snd_seq_ev_set_subs(&event);
    snd_seq_ev_set_direct(&event);
    event.flags = event.flags | SND_SEQ_EVENT_UMP;
    event.type = SND_UMP_MSG_TYPE_MIDI2_CHANNEL_VOICE;

    snd_ump_msg_midi2_t *m = (snd_ump_msg_midi2_t *)&event.ump;
    m->hdr.type = SND_UMP_MSG_TYPE_MIDI2_CHANNEL_VOICE;
    m->hdr.group = 0;
    m->hdr.channel = 0;

    m->hdr.status = SND_UMP_MSG_PROGRAM_CHANGE;

    while (1)
    {
        uint8_t n=0;
        printf("Program Change LSB/MSB/PC = ");
        n = scanf("%hhd %hhd %hhd", &lsb, &msb, &pc);
        if (n == 3)
        {
            m->program_change.program = pc & 0x7F;
            m->program_change.bank_valid = 1;
            m->program_change.bank_msb = msb & 0x7F;
            m->program_change.bank_lsb = lsb & 0x7F;
            snd_seq_ump_event_output(seq_handle, &event);
            snd_seq_drain_output(seq_handle);
        }
        else
        {
            break;
        }
    }

    // Close sequencer
    snd_seq_close(seq_handle);
    return 0;
}
