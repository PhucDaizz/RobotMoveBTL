#include <iostream>
using namespace std;

int main() {
    int n, count = 0;
    cin >> n;
    if (n>=0){
    	if (n==0){
    		cout<<1;
		}
    	else {
    		while (n != 0) {
        		count++;
        		n /= 10;
    		}
    		cout << count;
    	}
	}
    
    return 0;
}