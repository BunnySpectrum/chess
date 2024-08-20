
#include "game.h"


bool receive_input(std::string *input){
    std::getline(std::cin, *input);
    return !input->empty();
}

enum class InputState{
    Start,
    First,
    Delim,
    Second,
    End
};

typedef struct InputTokens{
    std::string leftToken;
    std::string rightToken;
}InputToken_s;

typedef struct MoveRequest{
    Location locStart;
    Location locEnd;
}MoveRequest_s;

Location process_alg_token(const std::string &token){
    char first = token[0];
    char second = token[1];

    int row = -1;
    int col = -1;

    if(first <= 'H'){
        first += 'a' - 'A';
    }

    if(first >= 'a' && first <= 'h'){
        col = first - 'a';
    }

    if(second >= '1' && second <= '8'){
        row = 7 - (second - '1');        
    }

    // RVO - return value optimization
    return Location(row, col);

}

MoveRequest_s process_tokens(const InputToken_s& tokens){

    MoveRequest_s move;
    move.locStart = process_alg_token(tokens.leftToken);
    move.locEnd = process_alg_token(tokens.rightToken);
    
    std::cout << "\t1: " << tokens.leftToken << " " << move.locStart << std::endl;
    std::cout << "\t2: " << tokens.rightToken << " " << move.locEnd << std::endl;

    return move;

}

void process_line(const std::string &input, InputToken_s *tokens){
    if(tokens == NULL){
        std::cout << "Null token passed to process_line." << std::endl;
        return;
    }

    // std::cout << "Got: " << input << std::endl;


    auto state = InputState::Start;
    for(const char val : input){
        switch(state){
            case InputState::Start:
                if(val != ' '){
                    // std::cout << "(" << val << ") Start -> First" << std::endl;
                    tokens->leftToken += val;
                    state = InputState::First;
                }
                break;
            case InputState::First:
                if(val == ' '){
                    // std::cout << "(" << val << ") -> Delim" << std::endl;
                    state = InputState::Delim;
                }else{
                    tokens->leftToken += val;
                }
                break;
            case InputState::Delim:
                if(val != ' '){
                    // std::cout << "(" << val << ") -> Second" << std::endl;
                    tokens->rightToken += val;
                    state = InputState::Second;
                }
                break;
            case InputState::Second:
                if(val == ' '){
                    // std::cout << "(" << val << ") -> End" << std::endl;
                    state = InputState::End;
                }else{
                    tokens->rightToken += val;
                }
                break;
            case InputState::End:
                break;
        }
    }
}

MoveRequest_s process_input(const std::string &input){
    InputToken_s tokens;

    process_line(input, &tokens);
    return process_tokens(tokens);
}





Game::Game(){
    board = Board();
    init_standard_board(&board);

    print_board(board);
    std::cout << std::endl;


}

void Game::Run(){
    std::cout << "Starting game." << std::endl;
    
    std::vector<Location> validMoves;
    std::string stroke;
    MoveRequest_s nextMove;


    while(receive_input(&stroke)){
        nextMove = process_input(stroke);
        std::cout << "Move from " << nextMove.locStart << " to " << nextMove.locEnd << std::endl;
        if(nextMove.locStart.is_invalid() || nextMove.locEnd.is_invalid()){
            std::cout << "\t Invalid move." << std::endl;
            continue;
        }

        validMoves = valid_moves_for_piece(board, nextMove.locStart);
        if(std::find(validMoves.cbegin(), validMoves.cend(), nextMove.locEnd) != validMoves.cend()){
            // locEnd is a valid move
            std::cout << "\t Valid." << std::endl; 
            move_piece(&board, nextMove.locStart, nextMove.locEnd);
        }else{
            std::cout << "\t Invalid." << std::endl;
        }
        
        print_board(board);

    }


}