#include <stdio.h>
#include <string.h>
#include <libssh/libssh.h>
#include "wireguard.h"

//MOSTLY an example program, read comments to understand planned additions 
// compile w/ gcc -o test playerclient.c wireguard.c -lssh


void wgkeygen(){


  // generate public key (if not already existing)

  // Generate a WireGuard public key
  wg_key privkey;
  wg_generate_private_key(privkey);

  wg_key_b64_string pubkeys;
  wg_key_to_base64(pubkeys, privkey);
  printf("here is my public key %s\n", pubkeys);

  return;
}

int main() {

    //prompt user to gen wireguard key before main setup 


  ssh_session session;
  int rc;

  // Initialize the SSH session
  session = ssh_new();
  if (session == NULL) {
    fprintf(stderr, "Error creating SSH session\n");
    return 1;
  }

  // Set the hostname and port of the remote SSH server
  ssh_options_set(session, SSH_OPTIONS_HOST, "example.com");
  ssh_options_set(session, SSH_OPTIONS_PORT, (void *)22);

  // Connect to the remote SSH server
  rc = ssh_connect(session);
  if (rc != SSH_OK) {
    fprintf(stderr, "Error connecting to the remote host: %s\n", ssh_get_error(session));
    return 1;
  }

  // Set the path to the private key file
  ssh_options_set(session, SSH_OPTIONS_IDENTITY, "~/.ssh/id_rsa");

  // Authenticate using the private key
  rc = ssh_userauth_publickey_auto(session, NULL, NULL);
  if (rc != SSH_AUTH_SUCCESS) {
    fprintf(stderr, "Error authenticating with the remote host: %s\n", ssh_get_error(session));
    return 1;
  }

  // Open a custom shell on the remote host
  ssh_channel channel = ssh_channel_new(session);
  if (channel == NULL) {
    fprintf(stderr, "Error creating channel: %s\n", ssh_get_error(session));
    return 1;
  }

  rc = ssh_channel_open_session(channel);
  if (rc != SSH_OK) {
    fprintf(stderr, "Error opening session: %s\n", ssh_get_error(session));
    return 1;
  }

    // Read commands from standard input and send them to the custom shell
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
    int nbytes = ssh_channel_write(channel, buffer, strlen(buffer));
    if (nbytes < 0) {
      fprintf(stderr, "Error sending command: %s\n", ssh_get_error(session));
      break;
    }
    
    // Read the standard output of the command
    char buffer2[1024];
    int nbytes2 = ssh_channel_read(channel, buffer2, sizeof(buffer2), 0);
    while (nbytes2 > 0) {
    printf("%.*s", nbytes2, buffer2);
    nbytes2 = ssh_channel_read(channel, buffer2, sizeof(buffer2), 0);
    }
  }


  // Close the channel and session
  ssh_channel_send_eof(channel);
  ssh_channel_close(channel);
  ssh_channel_free(channel);
  ssh_disconnect(session);
  ssh_free(session);

  return 0;
}