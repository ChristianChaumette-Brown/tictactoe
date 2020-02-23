#include <TicTac.h>
#include <iostream>
#include <Cell.h>

TicTac::TicTac(){
    dim=3;
    counter=0;
    computerP=false;
    
    std::vector<Cell> temp;
    for(int i=0; i<(dim*dim); i++){
        
        Board.push_back(Cell());
        oBoard.push_back(0);
        
    }
    
   
}
TicTac::TicTac(const TicTac& other){
    dim=other.dim;
    counter=other.counter;
    Board=other.Board;
    winner= other.winner;
    oBoard=other.oBoard;
    
}

ucm::json TicTac::getBoard(){
    ucm::json result;
    if(winner!=0){
        reset();
    }
    for(int i=0; i<(dim*dim); i++){
        
        //result.push_back(Board[i].state());
        oBoard[i]=Board[i].state();
    }
    //oBoard[1]=0;
    result["Board"]=oBoard;

    return result;
}

ucm::json TicTac::cellCheck(int i, int j){
    ucm::json result;
    
    
    int k = (i*3)+j;
    if(Board[k].filled==false){
    counter++;
    
    int player = counter %2;
    
    if(player== 1&&Board[k].filled==false){
        Board[k].setX();
        //oBoard[k]=1;
        oBoard[k]=Board[k].state();
        //result.push_back(oBoard[k]);
        
    }
    else if(player== 0&&Board[k].filled==false){
        Board[k].setO();
        //oBoard[k]=2;
        oBoard[k]=Board[k].state();
        //result.push_back(oBoard[k]);
    }
    }
    winCon();
    //result.push_back(Board[k].state());
    if(computerP==true&&winner==0){
        counter++;
      k =  aiPlay();
      int plai = counter %2;
      if(plai==0){
          Board[k].setO();
      }
      else if(plai==1){
          Board[k].setX();
      }
    
    oBoard[k]=Board[k].state();
      
    }
    result["Board"] = oBoard;
    
    return result;
}

ucm::json TicTac::winCon(){
    ucm::json result;
    /*if(winner!=0){
        reset();
    }*/
   
    //horizontal x check
    if((Board[0].tac=='x'&&Board[1].tac=='x'&&Board[2].tac=='x')||(Board[3].tac=='x'&&Board[4].tac=='x'&&Board[5].tac=='x')||(Board[6].tac=='x'&&Board[7].tac=='x'&&Board[8].tac=='x')){
        result["message"]="X winner";
        winner=1;
    }
    //horizontal o check
    else if((Board[0].tac=='o'&&Board[1].tac=='o'&&Board[2].tac=='o')||(Board[3].tac=='o'&&Board[4].tac=='o'&&Board[5].tac=='o')||(Board[6].tac=='o'&&Board[7].tac=='o'&&Board[8].tac=='o')){
        result["message"]="O winner";
        winner=1;
    }
    //diagonal x check
    else if((Board[0].tac=='x'&&Board[4].tac=='x'&&Board[8].tac=='x')||(Board[2].tac=='x'&&Board[4].tac=='x'&&Board[6].tac=='x')){
        result["message"]="X winner";
        winner=1;
    }
    else if((Board[0].tac=='o'&&Board[4].tac=='o'&&Board[8].tac=='o')||(Board[2].tac=='o'&&Board[4].tac=='o'&&Board[6].tac=='o')){
        result["message"]="O winner";
        winner=1;
    }
    else if((Board[0].tac=='x'&&Board[3].tac=='x'&&Board[6].tac=='x')||(Board[2].tac=='x'&&Board[5].tac=='x'&&Board[8].tac=='x')||(Board[1].tac=='x'&&Board[7].tac=='x'&&Board[4].tac=='x')){
        result["message"]= "X winner";
        winner=1;
    }
    else if((Board[0].tac=='o'&&Board[3].tac=='o'&&Board[6].tac=='o')||(Board[2].tac=='o'&&Board[5].tac=='o'&&Board[8].tac=='o')||(Board[1].tac=='o'&&Board[7].tac=='o'&&Board[4].tac=='o')){
        result["message"]= "O winner";
        winner=1;
    }
    else if(counter==9){
        result["message"]="No winner";
        winner=2;
    }
    
    
   
    
        result["winner"]=winner;
    
    


    return result;
}
ucm::json TicTac::reset(){
    ucm::json result;
    counter=0;
    winner=0;
    //computerP=false;
    for(int i=0; i<(dim*dim);i++){
        Board[i].reset();
        oBoard[i]= 0;
    }
    result["Board"]=oBoard;
    result["message"]="Game reset";
    result["winner"]=winner;

    return result;
}

ucm::json TicTac::aiPs(){
    ucm::json response;
    srand(time(NULL));
    if(computerP==false){
        computerP=true;
        response["message"]="AI on";
    }
    else{
        computerP=false;
        response["message"]="AI off";
    }
return response;
}

int TicTac::aiPlay(){
    if(counter==2){
        if(Board[4].filled==false){
            return 4;
        }
        else{
            randRs:
            int r = rand() %9;
            if(Board[r].filled==false&&(r==0||r==2||r==6||r==8)){
                return r;
            }
            else{
                goto randRs;
            }
        }
        
    }
    else {
//for(int i=0; i<(dim*dim);i++){
    //have win set ups above the block set ups inorder to assure more wins
    //set up a block of all possible win checks that will happen first then the block checks will happen
    //begin of win section
    
    if(((Board[0].tac=='o'&&Board[4].tac=='o')||(Board[2].tac=='o'&&Board[5].tac=='o')||(Board[6].tac=='o'&&Board[7].tac=='o'))&&Board[8].filled==false){
        return 8;
    }
    else if(((Board[7].tac=='o'&&Board[8].tac=='o')||(Board[2].tac=='o'&&Board[4].tac=='o')||(Board[0].tac=='o'&&Board[3].tac=='o'))&&Board[6].filled==false){
        return 6;
    }
    else if(((Board[1].tac=='o'&&Board[2].tac=='o')||(Board[4].tac=='o'&&Board[8].tac=='o')||(Board[6].tac=='o'&&Board[3].tac=='o'))&&Board[0].filled==false){
        return 0;
    }
    else if(((Board[6].tac=='o'&&Board[4].tac=='o')||(Board[8].tac=='o'&&Board[5].tac=='o')||(Board[0].tac=='o'&&Board[1].tac=='o'))&&Board[2].filled==false){
        return 2;
    }
    //wins for block 1
    else if(((Board[0].tac=='o'&&Board[2].tac=='o')||(Board[4].tac=='o'&&Board[7].tac=='o'))&&Board[1].filled==false){
        return 1;
    }
    else if(((Board[6].tac=='o'&&Board[8].tac=='o')||(Board[4].tac=='o'&&Board[1].tac=='o'))&&Board[7].filled==false){
        return 7;
    }
    else if(((Board[0].tac=='o'&&Board[6].tac=='o')||(Board[4].tac=='o'&&Board[5].tac=='o'))&&Board[3].filled==false){
        return 3;
    }
    else if(Board[4].tac=='o'&&Board[1].tac=='x'&&Board[8].tac=='x'&& counter == 4&&(Board[2].filled==false||Board[5].filled==false)){
        
        rs:
        int r = rand() %9;
        if (r ==2&&Board[2].filled==false){
            return 2;
        }
        else if( r==5&&Board[5].filled==false){
            return 5;
        }
        else{
            goto rs;
        }
    }
        else if(Board[4].tac=='o'&&Board[1].tac=='x'&&Board[6].tac=='x'&& counter == 4&&(Board[0].filled==false||Board[3].filled==false)){
        rs2:
        int r = rand() %9;
        if (r ==0&&Board[0].filled==false){
            return 0;
        }
        else if( r==3&&Board[3].filled==false){
            return 3;
        }
        else{
            goto rs2;
        }
        
    }
     else if(Board[4].tac=='o'&&Board[0].tac=='x'&&Board[7].tac=='x'&&counter==4&&(Board[6].filled==false||Board[3].filled==false)){
        rs1:
        int r = rand() %9;
        if (r ==6&&Board[6].filled==false){
            return 6;
        }
        else if( r==3&&Board[3].filled==false){
            return 3;
        }
        else{
            goto rs1;
        }
        
    }
    else if(Board[4].tac=='o'&&Board[2].tac=='x'&&Board[7].tac=='x'&&counter==4&&(Board[5].filled==false||Board[8].filled==false)){
        rs3:
        int r = rand() %9;
        if (r ==5&&Board[5].filled==false){
            return 5;
        }
        else if( r==8&&Board[8].filled==false){
            return 8;
        }
        else{
            goto rs3;
        }
        
    }
    else if(Board[4].tac=='o'&&Board[3].tac=='x'&&Board[8].tac=='x'&& counter == 4&&(Board[6].filled==false||Board[7].filled==false)){
        
        rs5:
        int r = rand() %9;
        if (r ==6&&Board[6].filled==false){
            return 6;
        }
        else if( r==7&&Board[7].filled==false){
            return 7;
        }
        else{
            goto rs5;
        }
    }
        else if(Board[4].tac=='o'&&Board[3].tac=='x'&&Board[2].tac=='x'&& counter == 4&&(Board[0].filled==false||Board[1].filled==false)){
        rs6:
        int r = rand() %9;
        if (r ==0&&Board[0].filled==false){
            return 0;
        }
        else if( r==1&&Board[1].filled==false){
            return 1;
        }
        else{
            goto rs6;
        }
        
    }
     else if(Board[4].tac=='o'&&Board[5].tac=='x'&&Board[6].tac=='x'&&counter==4&&(Board[7].filled==false||Board[8].filled==false)){
        rs7:
        int r = rand() %9;
        if (r ==7&&Board[7].filled==false){
            return 7;
        }
        else if( r==8&&Board[8].filled==false){
            return 8;
        }
        else{
            goto rs7;
        }
        
    }
    else if(Board[4].tac=='o'&&Board[5].tac=='x'&&Board[0].tac=='x'&&counter==4&&(Board[1].filled==false||Board[2].filled==false)){
        rs4:
        int r = rand() %9;
        if (r ==1&&Board[1].filled==false){
            return 1;
        }
        else if( r==2&&Board[2].filled==false){
            return 2;
        }
        else{
            goto rs4;
        }
        
    }
     else if(Board[4].tac=='o'&&Board[3].tac=='x'&&Board[2].tac=='x'&&Board[0].filled==false){
        return 0;
    }
    
    
    else if(((Board[2].tac=='o'&&Board[8].tac=='o')||(Board[4].tac=='o'&&Board[3].tac=='o'))&&Board[5].filled==false){
        return 5;
    }
    //begin of block section
     if(((Board[0].tac=='x'&&Board[4].tac=='x')||(Board[2].tac=='x'&&Board[5].tac=='x')||(Board[6].tac=='x'&&Board[7].tac=='x'))&&Board[8].filled==false){
        return 8;
    }
    if(((Board[7].tac=='x'&&Board[8].tac=='x')||(Board[2].tac=='x'&&Board[4].tac=='x')||(Board[0].tac=='x'&&Board[3].tac=='x'))&&Board[6].filled==false){
        return 6;
    }
    if(((Board[1].tac=='x'&&Board[2].tac=='x')||(Board[4].tac=='x'&&Board[8].tac=='x')||(Board[6].tac=='x'&&Board[3].tac=='x'))&&Board[0].filled==false){
        return 0;
    }
    if(((Board[6].tac=='x'&&Board[4].tac=='x')||(Board[8].tac=='x'&&Board[5].tac=='x')||(Board[0].tac=='x'&&Board[1].tac=='x'))&&Board[2].filled==false){
        return 2;
    }
    //wins for block 1
    else if(((Board[0].tac=='x'&&Board[2].tac=='x')||(Board[4].tac=='x'&&Board[7].tac=='x'))&&Board[1].filled==false){
        return 1;
    }
    else if(((Board[6].tac=='x'&&Board[8].tac=='x')||(Board[4].tac=='x'&&Board[1].tac=='x'))&&Board[7].filled==false){
        return 7;
    }
    else if(((Board[0].tac=='x'&&Board[6].tac=='x')||(Board[4].tac=='x'&&Board[5].tac=='x'))&&Board[3].filled==false){
        return 3;
    }
    else if(((Board[2].tac=='x'&&Board[8].tac=='x')||(Board[4].tac=='x'&&Board[3].tac=='x'))&&Board[5].filled==false){
        return 5;
    }
    //top left to bottom right diagonal bottom block
    else if(((Board[0].tac=='x'&&Board[4].tac=='x')||(Board[2].tac=='x'&&Board[5].tac=='x')||(Board[6].tac=='x'&&Board[7].tac=='x'))&&Board[8].filled==false){
        return 8;
    }/*
    else if(Board[2].tac=='x'&&Board[5].tac=='x'&&Board[8].filled==false){
        return 8;
    }
    else if(Board[2].tac=='x'&&Board[5].tac=='o'&&Board[8].filled==false){
        return 8;
    }
    else if(Board[6].tac=='x'&&Board[7]&&Board[8].filled==false){
        return 8;
    }*/
    
    //blocks for box1
    else if(((Board[0].tac=='x'&&Board[2].tac=='x')||(Board[4].tac=='x'&&Board[7].tac=='x'))&&Board[1].filled==false){
        return 1;
    }
    
    //blocks for box1
    else if(((Board[6].tac=='x'&&Board[8].tac=='x')||(Board[4].tac=='x'&&Board[1].tac=='x'))&&Board[7].filled==false){
        return 7;
    }
    else if(Board[4].tac=='x'&&Board[8].tac=='x'&&Board[0].filled==false){
        return 0;
    }
    //bottom right to top left win
    else if(Board[4].tac=='o'&&Board[8].tac=='o'&&Board[0].filled==false){
        return 0;
    }
    else if(Board[6].tac=='x'&&Board[4].tac=='x'&&Board[2].filled==false){
        return 2;
    }
    else if(Board[6].tac=='o'&&Board[4].tac=='o'&&Board[2].filled==false){
        return 2;
    }
    //top right to bottom left bootom block
    else if(Board[2].tac=='x'&&Board[4].tac=='x'&&Board[6].filled==false){
        return 6;
    }
    //left collum bottom block
    else if(Board[0].tac=='x'&&Board[3].tac=='x'&&Board[6].filled==false){
        return 6;
    }
    //left collum bottom win
    else if(Board[0].tac=='o'&&Board[3].tac=='o'&&Board[6].filled==false){
        return 6;
    }
    //left collum middle win
    else if(Board[0].tac=='x'&&Board[4].tac=='x' && Board[8].filled==true){
       randDig:
        int r = rand() %9;
        if((r==6&&Board[6].filled==false)||(r==2&&Board[2].filled==false)){
            return r;
        }
        else{
            goto randDig;
        }
        
    }
    else if(Board[2].tac=='x'&&Board[4].tac=='x' && Board[6].filled==true){
       randDig1:
        int r = rand() %9;
        if((r==0&&Board[0].filled==false)||(r==8&&Board[8].filled==false)){
            return r;
        }
        else{
            goto randDig1;
        }
        
    }
    else if(Board[6].tac=='x'&&Board[4].tac=='x' && Board[2].filled==true){
       randDig2:
        int r = rand() %9;
        if((r==0&&Board[0].filled==false)||(r==8&&Board[8].filled==false)){
            return r;
        }
        else{
            goto randDig2;
        }
        
    }
    else if(Board[8].tac=='x'&&Board[4].tac=='x' && Board[0].filled==true){
       randDig3:
        int r = rand() %9;
        if((r==6&&Board[6].filled==false)||(r==2&&Board[2].filled==false)){
            return r;
        }
        else{
            goto randDig3;
        }
        
    }
    else if(Board[8].tac=='x'&&Board[4].tac=='o' && Board[0].tac=='x'){
       randDig4:
        int r = rand() %9;
        if((r==1&&Board[1].filled==false)||(r==3&&Board[3].filled==false)||(r==5&&Board[5].filled==false)||(r==7&&Board[7].filled==false)){
            return r;
        }
        else{
            goto randDig4;
        }
        
    }
    else if(Board[2].tac=='x'&&Board[4].tac=='o' && Board[6].tac=='x'){
       randDig5:
        int r = rand() %9;
        if((r==1&&Board[1].filled==false)||(r==3&&Board[3].filled==false)||(r==5&&Board[5].filled==false)||(r==7&&Board[7].filled==false)){
            return r;
        }
        else{
            goto randDig5;
        }
        
    }
//pick first random available
else{
 randRs2:
            int r = rand() %9;
            if(Board[r].filled==false){
                return r;
            }
            else{
                goto randRs2;
            }
}
    
//}
    }



}