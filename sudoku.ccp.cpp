#include <iostream>
#include <ctime>
#include <limits>
using namespace std;

int grid[9][9]; // main sudoku grid

// print the sudoku (0 shown as .)
void print(int g[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(g[i][j]==0) cout<<". ";
            else cout<<g[i][j]<<" ";
            if((j+1)%3==0) cout<<"| "; // box separator
        }
        cout<<endl;
        if((i+1)%3==0) cout<<"---------------------"<<endl;
    }
}

// check if number can be placed at (r,c)
bool check(int r,int c,int num){
    for(int i=0;i<9;i++){
        if(grid[r][i]==num||grid[i][c]==num) return false; // row/col check
    }
    int sr=r-r%3,sc=c-c%3; // start of 3x3 box
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(grid[sr+i][sc+j]==num) return false; // box check
    return true;
}

// fill entire grid using backtracking
bool fillGrid(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(grid[i][j]==0){
                for(int num=1;num<=9;num++){
                    if(check(i,j,num)){
                        grid[i][j]=num;
                        if(fillGrid()) return true;
                        grid[i][j]=0; // backtrack
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// remove k numbers to create puzzle
void makePuzzle(int k){
    while(k>0){
        int i=rand()%9,j=rand()%9;
        if(grid[i][j]!=0){
            grid[i][j]=0;
            k--;
        }
    }
}

int main(){
    srand(time(0)); // random seed

    fillGrid(); // generate full sudoku

    int ans[9][9]; // store solution
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            ans[i][j]=grid[i][j];

    makePuzzle(45); // remove numbers

    cout<<"Sudoku Puzzle:\n";
    print(grid);

    cout<<"\nPress ENTER to see solution...";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();

    cout<<"\nSolution:\n";
    print(ans);

    return 0;
}