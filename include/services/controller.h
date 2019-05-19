#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
    public:
        void handle_request(const char *buffer, int socket);
};

#endif