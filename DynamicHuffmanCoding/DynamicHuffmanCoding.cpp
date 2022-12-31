// Dynamic_Huffman_Coding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
#define n 26
int d;
struct DynamicHuffmanCoding {
    bool S[n] = {false};          // Bieu dien bit dang ma hoa
    int M=0, E=0, R=0;        // bo dem trong so
    int P[n+1] = {0};         // con tro den node cha cua cac nut
    int C[2 * n] = {0};       // con tro den node con cua cac nut
    int A[n+1] = {0};         // Bieu dien bang chu cai
    int B[2 * n] = {0};       // tro den cac nut
    int W[2 * n] = {0};       // trong so cua nut
    int L[2 * n] = {0};       // con tro trai cac node
    int G[2 * n] = {0};       // con tro phai cac node
    int H;              // con tro node co trong so nho nhat
    int D[2 * n] = {0};     // con tro tro den cac node lon nhat trong 1 khoi
    int V;              // vi tri dau mang khong duoc dung lam so khoi
    int Z;              // hang so = 2n -1; gia tri nay chi vao node root
    int demreceive = 0;
    string receive = "";
    // Khoi tao
    void Initlialize() {
        int i;
        // Khoi tao bo dem trong so 0 = 0;
        M = 0;
        E = 0;
        R = -1;
        //Gan gia tri cho Z
        Z = 2 * n - 1;
        // Dem trong so
        for (i = 1; i <= n; i++) {
            M++;
            R++;
            if (2 * R == M) {
                E++;
                R = 0;
            }
            //
            A[i] = C[i] = i;// a,b,c,d,e,...,z
        }
        // M = 2^4 + 11; R = 11; E = 4
        //char x = A[i] + 'a' - 1;
        H = 1; // NYT
        L[H] = G[H] = H; // ****
        W[H] = 0;
        D[H] = A[0] = Z; //A[0] vai tro` node root
        V = 2;//***
        for (i = V; i <= Z - 1; i++) {
            G[i] = i + 1;
        }
        G[Z] = 0;//***
        P[n] = 0;// NULL
        C[Z] = 0;//NULL
        B[Z] = H;//node root = 1;
    }
    
    //Ma hoa phan tu thu k
    void Encode(int k) {
        int i, j, q, t; // q: con tro node || t: so bit de bieu dien
        i = 0;
        q = A[k];
        if (q <= M) {//xet truong hop dem bit ma hoa
            printf("encode zero weight\n");
            q = q - 1; // 
            if (q < 2 * R) t = E + 1;
            else {
                q = q - R;// xac dinh lai node
                t = E;
            }
            for (j = 1; j <= t; j++) {//gan bit cho node
                i++;
                S[i]  = q % 2;               
 //               receive += int(S[i]) + '0';
                q = q / 2;
            }
            q = A[0];
        }
        while (q < Z) {// gan bit
            i++;
            S[i] = (q + 1) % 2;
 //           receive += int(S[i]) + '0';
            q = P[(q + 1) / 2];
        }
        while (i > 0) {
            printf("%d", S[i]);
          receive += int(S[i]) + '0';
            i--;
        }
        printf("| %c", k + 'a' - 1);
        printf("\n");
    }

    // Giai ma
    int Decode(){
        int j, q;
        q = Z;
        cout << endl;
        while (A[C[q]] != q) {// neu q la internal thi thuc hien vong lap
            q = 2 * C[q] - 1 + receive[demreceive++] -'0';// receive ??
        }
        // q external
        if (C[q] == 0) {
            printf("decode zero weight\n");
            q = 0;
            for (j = 1; j <= E; j++) {
                q = 2 * q + receive[demreceive++] - '0';
            }
            if (q < R){
                q = 2 * q + receive[demreceive++] - '0';
            }
            else q = q + R;
            q++;
        }
        return C[q];//
    }

    //Doi cho 2 cay con q va t
    void Exchange(int q, int t) {
        int ct, cq, acq;
        ct = C[t]; cq = C[q], acq = A[cq];
        if (A[ct] != t) P[ct] = q;
        else A[ct] = q;

        if (acq != q) P[cq] = t;
        else A[cq] = t;
        C[t] = cq; C[q] = ct;
    }

    //Cap nhap node k
    void Update(int k) {
        int q;
        //Set q to the external node whosr weight should increase
        q = A[k];
        if (q <= M) {
            printf("a zero weight will become positive\n");
            A[C[M]] = q; C[q] = C[M];
            if (R == 0) {// Khoi tao lai bo dem trong so 0
                R = M / 2;
                if (R > 0) E--;
            }
            M--; R--;
            if (M > 0) {// con trong so 0
                q = A[0] - 1;//q= z-2
                A[0] = q - 1;
                A[k] = q;
                C[q] = k;
                if (M > 1) C[q - 1] = 0;
                P[M] = q + 1;
                C[q + 1] = M;
                B[q] = B[q - 1] = H;
            }
        }
        //Set q to the external node whosr weight should increase
        while (q > 0) {
  //          printf("q4");
            //Move q to the right of its block
            if (q < D[B[q]] && D[B[P[(q + 1) / 2]]] > q + 1) {
                Exchange(q, D[B[q]]);
                q = D[B[q]];
            }
            //Move q to the right of its block

            //Transfer q to the next block, with weight one higher
            int u, gu, lu, x, t, qq;//u: bac cua node
            u = B[q];
            gu = G[u];
            lu = L[u];
            x = W[u];
            qq = D[u];
            if (W[gu] == x + 1) {
                B[q] = B[qq] = gu;
                if (D[lu] == q - 1 || (u == H && q == A[0])){
                    printf("block u disappears\n");
                    G[lu] = gu;
                    L[gu] = lu;
                    if(H == u) H = gu;
                    G[u] = V;
                    V = u;
                }
                else D[u] = q - 1;
            }
            else if(D[lu] == q - 1 || (u == H && q == A[0])) W[u] = x + 1;
            else {
                printf("a new block appears\n");
                t = V;
                V = G[V];
                L[t] = u;
                G[t] = gu;
                L[gu] = G[u] = t;
                W[t] = x + 1; D[t] = D[u]; D[u] = q - 1;
                B[q] = t;
                B[qq] = t;
            }
            q = qq;
//Transfer q to the next block, with weight one higher
            q = P[(q + 1) / 2];
        }
    }

    //Cap nhap node k
    void Downdate(int k) {
        int q;
        q = A[k]; printf("q > M\n");
        while (q > 0) {
            //Move q to the left block of its block
            int u, t;
            u = B[q];
            if (u == H) t = 1;
            else t = D[L[u]] + 1;
            printf("q is not the parent of t\n");
            if (q != t) {
                Exchange(q, t);
                q = t;
            }
            //Move q to the left block of its block

            //Transfer q to the previous block, with weight one lower
            int lu, x;
            u = B[q]; lu = L[u]; x = W[u];
            if (W[lu] == x - 1) {
                B[q] = lu;
                D[lu] = q;
                if (D[u] == q) {
                    printf("block u dissapears\n");
                    G[lu] = G[u];
                    L[G[u]] = lu;
                    G[u] = V; V = u;
                }
            }
            else if (D[u] == q) W[u] = x - 1;
            else {
                printf("a new block appears");
                t = V;
                V = G[V];
                if (u == H) H = t;
                L[t] = lu;
                G[t] = u;
                G[lu] = L[u] = t;
                W[t] = x - 1;
                D[t] = q;
                B[q] = t;
            }
            if (A[C[q]] != q && B[q] == B[2 * C[q]] && q > 2 * C[q] + 1) Exchange(2 * C[q] + 1, q);
            //Transfer q to the previous block, with weight one lower
            q = P[(q + 1) / 2];
            if (W[B[A[k]]] == 0) {
                //Absord zero-weight letter ak
                M++; R++;
                if (M > 1) {
                    printf("there are three nodes of weight zero\n");
                    if (2*R == M){
                        E++;
                        R = 0;
                    }
                    q = A[0] + 2; A[0] = q; C[q] = 0;
                    A[k] = M; C[M] = k;
                }
                //Absord zero-weight letter ak
            }
        }
    }
};

void debug(DynamicHuffmanCoding a){
    cout << "\nA: ";
    for(int i=0;i<=n;i++){
        cout << a.A[i] <<" ";
    }
    cout << "\nP: ";
    for(int i=0;i<=n;i++){
        cout << a.P[i] <<" ";
    }
    cout << "\nS: ";
    for(int i=0;i<n;i++){
        cout << a.S[i] <<" ";
    }
    cout << "\nB: ";
    for(int i=0;i<2*n;i++){
        cout << a.B[i] <<" ";
    }
    cout << "\nW: ";
    for(int i=0;i<2*n;i++){
        cout << a.W[i] <<" ";
    }
    cout << "\nC: ";
    for(int i=0;i<2*n;i++){
        cout << a.C[i] <<" ";
    }
    cout << "\nL: ";
    for(int i=0;i<2*n;i++){
        cout << a.L[i] <<" ";
    }
    cout << "\nG: ";
    for(int i=0;i<2*n;i++){
        cout << a.G[i] <<" ";
    }
    cout << "\nD: ";
    for(int i=0;i<2*n;i++){
        cout << a.D[i] <<" ";
    }
}

void input(string &s){
    cin >> s;
}

int main()
{
    DynamicHuffmanCoding a;
    a.Initlialize();
    fstream encode;   // mo file de doc
    fstream decode;
    int choose;
    do{
        cout << "1: encode| 2: decode: ";
        cin >> choose;
    }while(choose != 1 && choose != 2);
    string s;
    if(choose == 1){
        int tmp;
        encode.open("encode.txt", ios::in);
        decode.open("decode.txt", ios::out);
        cout <<"Encode from file (1: Yes|| 2:No): ";
        cin >> tmp;
        if(tmp==1)
            getline(encode, s);
        else{
            input(s);
        }
        for(int i=0;i<s.length();i++){
            a.Encode(s[i] - 'a' + 1);
            a.Update(s[i] - 'a' + 1);
        }
        decode << a.receive;
    }
    if(choose == 2){
        int tmp;
        encode.open("encode.txt", ios::out);
        decode.open("decode.txt", ios::in);
        cout <<"Decode from file (1: Yes|| 2:No): ";
        cin >> tmp;
        if(tmp==1)
            getline(decode, s);
        else{
            input(s);
        }
        a.receive = s;
        cout << a.receive;
        a.demreceive = 0;
        string output ="";
        while(a.demreceive < a.receive.length()){
            int tmp = a.Decode();
            output += char(tmp + 'a' -1);
            a.Update(tmp);
        }
        encode << output;
    }
    encode.close();
    decode.close();
//00000010010000011011101011101100100100010100000001000000111011100111001101011100100110111101101110101010111101101
}
