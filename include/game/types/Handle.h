#ifndef GAME_TYPES_HANDLE_H
#define GAME_TYPES_HANDLE_H

struct Handle {
    virtual ~Handle();
    virtual void Stop();
};

#endif /* GAME_TYPES_HANDLE_H */
