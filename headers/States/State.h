#ifndef GAMESTATE_H
#define GAMESTATE_H

/*
    State class

    Every game state derives from this class (only 3 states yet)
*/

namespace States {
    enum GameState {
        EDITOR,
        MAIN_MENU,
        GAME
    };

    class State {
        protected:
            GameState _state;

        public:
            State () {};
            State (GameState state) : _state(state) {};
            ~State(){};
            virtual void StartState () = 0;
            virtual void UpdateState () = 0;
            virtual void EndState () = 0;

            GameState GState () {return _state;};
    };
}

#endif
