#include <iostream>
using namespace std;



void printResult(const char* name,int hit,int fault,int n){
    cout<<"\n----- "<<name<<" -----\n";
    cout<<"Total Page Hit = "<<hit<<endl;
    cout<<"Total Page Fault = "<<fault<<endl;
    cout<<"Hit Ratio = "<<(float)hit/n<<endl;
    cout<<"Fault Ratio = "<<(float)fault/n<<endl;
}

int main(){
    int n,f;
    cout<<"Enter number of pages: ";
    cin>>n;
    int page[n];
    cout<<"Enter page reference string: ";
    for(int i=0;i<n;i++) cin>>page[i];
    cout<<"Enter number of frames: ";
    cin>>f;

    // FIFO
    {
        int frame[f]; for(int i=0;i<f;i++) frame[i]=-1;
        int front=0,hit=0,fault=0;
        for(int i=0;i<n;i++){
            bool found=false;
            for(int j=0;j<f;j++) if(frame[j]==page[i]){found=true;break;}
            if(found) hit++;
            else{ frame[front]=page[i]; front=(front+1)%f; fault++; }
        }
        printResult("FIFO",hit,fault,n);
    }

    // Optimal
    {
        int frame[f]; for(int i=0;i<f;i++) frame[i]=-1;
        int hit=0,fault=0;
        for(int i=0;i<n;i++){
            bool found=false;
            for(int j=0;j<f;j++) if(frame[j]==page[i]){found=true;break;}
            if(found) hit++;
            else{
                fault++;
                bool empty=false;
                for(int j=0;j<f;j++) if(frame[j]==-1){frame[j]=page[i]; empty=true; break;}
                if(!empty){
                    int pos=-1,farthest=-1;
                    for(int j=0;j<f;j++){
                        int k;
                        for(k=i+1;k<n;k++) if(frame[j]==page[k]) break;
                        if(k==n){pos=j; break;}
                        if(k>farthest){farthest=k; pos=j;}
                    }
                    frame[pos]=page[i];
                }
            }
        }
        printResult("OPTIMAL",hit,fault,n);
    }

    // LRU
    {
        int frame[f]; for(int i=0;i<f;i++) frame[i]=-1;
        int hit=0,fault=0;
        for(int i=0;i<n;i++){
            bool found=false;
            for(int j=0;j<f;j++) if(frame[j]==page[i]){found=true;break;}
            if(found) hit++;
            else{
                fault++;
                bool empty=false;
                for(int j=0;j<f;j++) if(frame[j]==-1){frame[j]=page[i]; empty=true; break;}
                if(!empty){
                    int pos=-1,least=i;
                    for(int j=0;j<f;j++){
                        int k;
                        for(k=i-1;k>=0;k--) if(frame[j]==page[k]) break;
                        if(k<least){least=k; pos=j;}
                    }
                    frame[pos]=page[i];
                }
            }
        }
        printResult("LRU",hit,fault,n);
    }

    // MRU
    {
        int frame[f]; for(int i=0;i<f;i++) frame[i]=-1;
        int hit=0,fault=0;
        for(int i=0;i<n;i++){
            bool found=false;
            for(int j=0;j<f;j++) if(frame[j]==page[i]){found=true;break;}
            if(found) hit++;
            else{
                fault++;
                bool empty=false;
                for(int j=0;j<f;j++) if(frame[j]==-1){frame[j]=page[i]; empty=true; break;}
                if(!empty){
                    int pos=-1,recent=-1;
                    for(int j=0;j<f;j++){
                        int k;
                        for(k=i-1;k>=0;k--) if(frame[j]==page[k]) break;
                        if(k>recent){recent=k; pos=j;}
                    }
                    frame[pos]=page[i];
                }
            }
        }
        printResult("MRU",hit,fault,n);
    }
    return 0;
}
