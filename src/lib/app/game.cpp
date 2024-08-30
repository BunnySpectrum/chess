
#include "game.h"





bool receive_input(std::string *input){
    std::getline(std::cin, *input);
    return !input->empty();
}


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




Player::Player(PieceColor_e color) : color_(color){
    ;
}

HumanPlayer::HumanPlayer(PieceColor_e color) : Player{color}{
    ;
}

// int32_t HumanPlayer::score(const Board& board){
//     return 0;
// }

std::optional<MoveRequest_s> HumanPlayer::pick_move(const Board& board) {
    std::vector<Location> validMoves;
    std::string stroke;
    MoveRequest_s nextMove;

    while(receive_input(&stroke)){
        nextMove = process_input(stroke);

        if(nextMove.locStart.is_invalid() || nextMove.locEnd.is_invalid()){
            std::cout << "\t Invalid move." << std::endl;
            continue;
        }


        validMoves = valid_moves_for_piece(board, nextMove.locStart);
        if(std::find(validMoves.cbegin(), validMoves.cend(), nextMove.locEnd) != validMoves.cend()){
            // locEnd is a valid move
        
            // TODO refactor so move created in one step
            nextMove.pieceStart = board.get_piece(nextMove.locStart);
            nextMove.pieceEnd = board.get_piece(nextMove.locEnd);

            return nextMove;
        }else{
            std::cout << "\t Invalid." << std::endl;
        }
    }
    return std::nullopt;
}


CpuPlayer::CpuPlayer(PieceColor_e color) : Player{color}{
    ;
}

enum Material : int32_t{
    Pawn = 1,
    Bishop = 3,
    Knight = 3,
    Rook = 5,
    Queen = 9,
    King = 100
};

int32_t CpuPlayer::score(const Board& board, PieceColor_e color){
    auto pieceLocations = board.getLocationsForColor(color);
    // Pawn advancement
    // +0 if on starting row
    // +1 for each row
    int32_t pawnScore = 0;
    int32_t materialScore = 0;


    int pawnHomeRow = color == COLOR_BLACK ? 1 : 6;
    for(const Location pieceLoc : pieceLocations){
        Piece piece = board.get_piece(pieceLoc);
        switch(piece.id()){
            case PIECE_PAWN:
            case PIECE_PAWN_FIRST:
                pawnScore += abs(pieceLoc.row() - pawnHomeRow);
                materialScore += Material::Pawn;
                break;
            case PIECE_BISHOP:
                materialScore += Material::Bishop;
                break;
            case PIECE_KNIGHT:
                materialScore += Material::Knight;
                break;
            case PIECE_ROOK:
            case PIECE_ROOK_FIRST:
                materialScore += Material::Rook;
                break;
            case PIECE_QUEEN:
                materialScore += Material::Queen;
                break;
            case PIECE_KING:
            case PIECE_KING_FIRST:
                materialScore += Material::King;
                break;
            default:
                break;
        }
    }
    // std::cout << pieceColorToSymbol(color) << " " << pawnScore << std::endl;
    return pawnScore + materialScore*10;
}

int32_t CpuPlayer::negamax(const Board& board, int depth, PieceColor_e color){
    std::vector<Location> endLocations;
    std::optional<MoveRequest_s> finalMove;// = std::nullopt;
    std::vector<MoveRequest_s> possibleMoves;

    // std::cout << "Negamax: color = " << pieceColorToSymbol(color) << " depth = " << depth << std::endl;

    if(depth == 0){
        // At the extent of the search. 
        // Score this board
        auto scale = color == color_ ? 1 : -1;
        // print_board(board);
        return score(board, color) * scale;
    }else{
        // Build a new board of possible moves for the other color
        // Then recurse
        auto pieceLocations = board.getLocationsForColor(color);
    
        for(const Location& startLoc : pieceLocations){
            endLocations = valid_moves_for_piece(board, startLoc);

            for(const Location testLoc : endLocations){
                Board testBoard = board;
                move_piece(&testBoard, startLoc, testLoc);
                
                auto nextColor = color == COLOR_BLACK ? COLOR_WHITE : COLOR_BLACK;
                return negamax(testBoard, depth-1, nextColor);
            }
        }
    }
    return INT32_MIN;
}


std::optional<MoveRequest_s> CpuPlayer::search_for_move(const Board& board){
    std::vector<Location> endLocations;
    std::optional<MoveRequest_s> finalMove;// = std::nullopt;
    std::vector<MoveRequest_s> possibleMoves;

    // Get list of all locations where we have a piece
    auto pieceLocations = board.getLocationsForColor(color_);

    auto nextColor = color_ == COLOR_BLACK ? COLOR_WHITE : COLOR_BLACK;

    for(const Location& startLoc : pieceLocations){
        // For each location, get a list of locations that piece could move to
        endLocations = valid_moves_for_piece(board, startLoc);
        
        // For each move, search the tree and get the best score from the end.
        for(const Location testLoc : endLocations){
            Board testBoard = board;
            move_piece(&testBoard, startLoc, testLoc);

            auto score = negamax(testBoard, 5, nextColor);

            // At this point we have the best score from going down this branch
            auto& move = possibleMoves.emplace_back();
            move.locStart = startLoc;
            move.locEnd = testLoc;
            move.pieceStart = testBoard.get_piece(move.locStart);
            move.pieceEnd = testBoard.get_piece(move.locEnd);
            move.score = score;

        }
    }

    // Go through the moves we found and return the best one
    int32_t bestScore = INT32_MIN;
    for(const MoveRequest_s& candidateMove : possibleMoves){
        if(candidateMove.score > bestScore){
            finalMove = candidateMove;
            bestScore = candidateMove.score;
        }
    }

    return finalMove;
}

std::optional<MoveRequest_s> CpuPlayer::pick_move(const Board& board){
    max_search_depth = 3;

    return search_for_move(board);
}


Game::Game(){
    board = Board();
    init_standard_board(&board);

    print_board(board);
    std::cout << std::endl;
}

void Game::Run(){
    std::cout << "Starting game." << std::endl;

    HumanPlayer human(COLOR_WHITE);
    CpuPlayer computer(COLOR_BLACK);


    do{
        // Human move
        {
            auto optNextMove = std::move(human.pick_move(board));
            if(!optNextMove.has_value()){
                std::cout << "Human has quit" << std::endl;
                break;
            }
            auto nextMove = optNextMove.value();
            move_piece(&board, nextMove.locStart, nextMove.locEnd);
        }

        print_board(board);
        std::cout << std::endl;

        // Cpu move
        {
            auto optNextMove = computer.pick_move(board);
            if(!optNextMove.has_value()){
                std::cout << "Cpu has quit" << std::endl;
                break;
            }
            auto nextMove = optNextMove.value();

            std::cout << "CPU Move from " << locationToAlg(nextMove.locStart) << " to " << locationToAlg(nextMove.locEnd) << std::endl;
            move_piece(&board, nextMove.locStart, nextMove.locEnd);
        }

        print_board(board);
        std::cout << std::endl;
    }while(true);


}