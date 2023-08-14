#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
struct Robot {
    int x; // vị trí hàng của robot trên ma trận     
    int y; // vị trí cột của robot trên ma trận     
    vector<pair<int, int>> path; // đường đi của robot lưu trữ cho hàm robotMove
    vector<pair<int, int>> path2; // đường đi của robot lưu trữ cho hàm robotMoveTurn
};

void robotMove(vector<vector<int> >& arr, vector<vector<bool> >& visited, int x, int y, vector<pair<int,int> >& path) {
    int maxVal = 0;
    int nextX = x;
    int nextY = y;

    if (x > 0 && !visited[x-1][y] && arr[x-1][y] > maxVal) {
        maxVal = arr[x-1][y];
        nextX = x-1;  	// Robot sẽ đi lên 
        nextY = y;
    }
    
    if (x < arr.size()-1 && !visited[x+1][y] && arr[x+1][y] > maxVal) {
        maxVal = arr[x+1][y];
        nextX = x+1;  	// Robot sẽ đi xuống 
        nextY = y;	
    }
    if (y > 0 && !visited[x][y-1] && arr[x][y-1] > maxVal) {
        maxVal = arr[x][y-1];
        nextX = x;  	// Robot sẽ đi sang trái 
        nextY = y-1;
    }
    if (y < arr[0].size()-1 && !visited[x][y+1] && arr[x][y+1] > maxVal) {
        maxVal = arr[x][y+1];
        nextX = x;  	// Robot sẽ đi sang phải
        nextY = y+1;
    }
    

    if (maxVal > 0) {
        visited[nextX][nextY] = true;
        path.push_back(make_pair(nextX,nextY));
        robotMove(arr, visited, nextX, nextY,path);
    }
}


void robotMoveTurns(vector<vector<int> >& arr, vector<vector<bool> >& visited, int x, int y, vector<pair<int,int> >& path) {
    int maxVal = 0;
    int nextX = x;
    int nextY = y;

    if (x > 0 && !visited[x-1][y] && arr[x-1][y] > maxVal) {
        maxVal = arr[x-1][y];
        nextX = x-1;  	// Robot sẽ đi lên 
        nextY = y;
    }
    
    if (x < arr.size()-1 && !visited[x+1][y] && arr[x+1][y] > maxVal) {
        maxVal = arr[x+1][y];
        nextX = x+1; 	// Robot sẽ đi xuống 
        nextY = y;
    }
    if (y > 0 && !visited[x][y-1] && arr[x][y-1] > maxVal) {
        maxVal = arr[x][y-1];
        nextX = x;  	// Robot sẽ đi sang trái 
        nextY = y-1;
    }
    if (y < arr[0].size()-1 && !visited[x][y+1] && arr[x][y+1] > maxVal) {
        maxVal = arr[x][y+1];
        nextX = x; 		// Robot sẽ đi sang phải
        nextY = y+1;
    }
    

    if (maxVal > 0) {
        visited[nextX][nextY] = true;
        path.push_back(make_pair(nextX,nextY));
    }
}

void visualizePath(vector<vector<int>>& arr, vector<pair<int,int>>& path, ofstream& fileOut) {
    vector<vector<int>> steps(arr.size(), vector<int>(arr[0].size(), -1));
    for (int i = 0; i < path.size(); i++) {
        steps[path[i].first][path[i].second] = i + 1;
    }
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            if (steps[i][j] != -1) {
                if (steps[i][j] >= 10 ){
                	fileOut << steps[i][j] << "   ";
				}
				else {
					fileOut << steps[i][j] << "    ";
				}
				
            } else {
                fileOut << " .   ";
            }
        }
        fileOut << endl;
    }
}




int main() {
     
    int rows, cols;
    ifstream file("input.txt");
    ofstream fileOut("output.txt");
    file >> rows >> cols;
    vector<vector<int> > arr(rows, vector<int>(cols)); 
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            file >> arr[i][j];
        } 
    }
    
    int n;
  
    file>> n;
    switch (n){
    	case 1: {
    // Đọc dữ liệu đầu vào
    		Robot robot1;
    		file >> robot1.x >> robot1.y;
    		int count=0;;
    // Khởi tạo biến
    	// Đánh dấu vị trí robot đã đi qua 
    		vector<vector<bool> > visited1(rows, vector<bool>(cols, false));  // Dùng cho hàm robotMove  
    		vector<vector<bool> > visited2(rows, vector<bool>(cols, false));  // Dùng cho hàm robotMoveTurn
    		
    	// Lưu và đánh dấu nơi đặt robot 
    		robot1.path.push_back(make_pair(robot1.x, robot1.y));
    		robot1.path2.push_back(make_pair(robot1.x,robot1.y));
    		visited1[robot1.x][robot1.x] = true;
    		visited2[robot1.x][robot1.x] = true;
    		
    		
    		robotMove(arr, visited1, robot1.x, robot1.y,robot1.path);
    		for(auto p : robot1.path){
        		count ++;
    		}
    		fileOut<< "Tổng số ô mà ROBOT đã đi là: " << count << endl;
    		fileOut <<"Các vị trí mà ROBOT đã đi là: ";
    		for (auto p : robot1.path) {
        		fileOut << arr[p.first][p.second] << " ";
    		}
    		fileOut<<endl;
    		fileOut << "Đường đi của ROBOT: " << endl;
			visualizePath(arr, robot1.path, fileOut);	


    // Tìm đường đi cho robot
    		bool canMove = true;
    		while (canMove) {
        		canMove = false;

    	// Hiển thị trạng thái của ma trận
        		fileOut << "Trạng thái của ma trận sau " << robot1.path2.size() - 1 << " bước:" << endl;
        		visualizePath(arr, robot1.path2, fileOut);
				fileOut<<endl;
    	// Tìm đường đi tiếp theo cho robot
        		int prevSize = robot1.path2.size();
        		robotMoveTurns(arr, visited2, robot1.x, robot1.y, robot1.path2);
        		if (robot1.path2.size() > prevSize) {
            		canMove = true;
            		robot1.x = robot1.path2.back().first;
            		robot1.y = robot1.path2.back().second;
        		}
    		}
    		break;
		}
     
       case 2: {
    // Đọc dữ liệu đầu vào
   			Robot robot1, robot2;
    		file >> robot1.x >> robot1.y;
    		file >> robot2.x >> robot2.y;
    // Khởi tạo biến
    		vector<vector<bool> > visited1(rows, vector<bool>(cols, false));
    		vector<vector<bool> > visited2(rows, vector<bool>(cols, false));
    		visited1[robot1.x][robot1.y] = true;
    		visited2[robot2.x][robot2.y] = true;
    		robot1.path.push_back(make_pair(robot1.x, robot1.y));
    		robot2.path.push_back(make_pair(robot2.x, robot2.y));
			int count1=0,count2=0;
			
    // Tìm đường đi cho robot 1
    		robotMove(arr, visited1, robot1.x, robot1.y, robot1.path);
    		for(auto p : robot1.path){
        		count1 ++;
    		}
    		fileOut<< "Tổng số ô mà ROBOT 1 đã đi là: " << count1 << endl;
    		fileOut << "Các vị trí mà ROBOT 1 đã đi là: ";
    		for (auto p : robot1.path) {
        		fileOut << arr[p.first][p.second] << " ";
    		}
    		fileOut << endl;
    		fileOut << "Đường đi của ROBOT 1 : " << endl;
			visualizePath(arr, robot1.path, fileOut);

    // Tìm đường đi cho robot 2
    		robotMove(arr, visited2, robot2.x, robot2.y, robot2.path);
    		for(auto p : robot2.path){
        		count2 ++;
    		}
    		fileOut<< "Tổng số ô mà ROBOT 2 đã đi là: " << count2 << endl;
    		fileOut << "Các vị trí mà ROBOT 2 đã đi là: ";
    		for (auto p : robot2.path) {
        		fileOut << arr[p.first][p.second] << " ";
    		}
    		fileOut <<endl<< "Đường đi của ROBOT 2 : " << endl;
			visualizePath(arr, robot2.path, fileOut);
    		fileOut << endl;

    // Tìm và xuất vị trí trùng nhau
    		fileOut << "Các vị trí mà hai ROBOT đã đi trùng là: ";
    		int dups = 0;
    		for (int i = 0; i < robot1.path.size(); i++) {
        		for (int j = 0; j < robot2.path.size(); j++) {
            		if (robot1.path[i].first == robot2.path[j].first && robot1.path[i].second == robot2.path[j].second) {
                		fileOut << "(" << robot1.path[i].first << ", " << robot1.path[i].second << ") ";
                		dups ++;
            		}
        		}
    		}
    		fileOut << endl;
    		fileOut << "Số vị trí trùng nhau là: "<<dups<<endl;
    		// Hiển thị trạng thái của ma trận sau mỗi bước
    		int maxStep = max(robot1.path.size(), robot2.path.size());
    		for (int step = 0; step < maxStep; step++) {
    			// cái này nó tạo mảng path1 2 chiều, sao chép lại mảng path. lệnh robot1.path.begin() là 
    			// dung để trỏ tới phần từ đầu của mảng robot1.path
    			// robot1.path.begin() + min(step + 1, (int)robot1.path.size())
    			// cái này là trở tới phần tử sau mỗi lần chạy vòng lặp for nó cộng thêm
    			// giá trị nhỏ nhất của step + 1   hoặc  (int)robot1.path.size()
    			// vậy thà ghi step + 1 đi nhưng tại vì lỡ cái step +1 nó lớn hơn (int)robot1.path.size()
    			// sao, vậy dẫn đến nó sao chép bị thừa đi Điều này có thể dẫn đến lỗi trong trường hợp kích 
				// thước của vector robot1.path nhỏ hơn step + 1 .
        		vector<pair<int,int>> path1(robot1.path.begin(), robot1.path.begin() + min(step + 1, (int)robot1.path.size()));
        		vector<pair<int,int>> path2(robot2.path.begin(), robot2.path.begin() + min(step + 1, (int)robot2.path.size()));

        		fileOut << "Trạng thái của ma trận sau khi hai ROBOT đã đi xong " << step << " bước:" << endl;
        		fileOut << "ROBOT1"<<endl;
        		visualizePath(arr, path1, fileOut);
        		fileOut << "ROBOT2"<<endl;
        		visualizePath(arr, path2, fileOut);
        		fileOut<<endl<<"----------------------------"<<endl;
    		}

    		break;
		}



		case 3: {
    // Đọc dữ liệu đầu vào
    		Robot robot1, robot2;
    		file >> robot1.x >> robot1.y;
   			file >> robot2.x >> robot2.y;

    // Khởi tạo biến
    		vector<vector<bool> > visited(rows, vector<bool>(cols, false));
    		visited[robot1.x][robot1.y] = true;
    		visited[robot2.x][robot2.y] = true;
    		robot1.path.push_back(make_pair(robot1.x, robot1.y));
    		robot2.path.push_back(make_pair(robot2.x, robot2.y));

    		bool canMove = true;
    		while (canMove) {
        		canMove = false;

        // Tìm đường đi tiếp theo cho robot 1
        		int prevSize = robot1.path.size();
        		robotMoveTurns(arr, visited, robot1.x, robot1.y, robot1.path);
        		if (robot1.path.size() > prevSize) {
            		canMove = true;
            		robot1.x = robot1.path.back().first;
            		robot1.y = robot1.path.back().second;
        		}

        // Tìm đường đi tiếp theo cho robot 2
        		prevSize = robot2.path.size();
        		robotMoveTurns(arr, visited, robot2.x, robot2.y, robot2.path);
        		if (robot2.path.size() > prevSize) {
            		canMove = true;
            		robot2.x = robot2.path.back().first;
            		robot2.y = robot2.path.back().second;
        		}
    		}

    // Xuất kết quả
    		int count1=0,count2=0;
    		for (auto p : robot1.path) {
        		count1++;
    		}
    		fileOut << "Số ô ROBOT1 đã đi là: "<<count1<<endl;
    		fileOut << "Các vị trí mà ROBOT 1 đã đi là: ";
    		for (auto p : robot1.path) {
        		fileOut << arr[p.first][p.second] << " ";
    		}
    		fileOut << endl;

    		fileOut << "Đường đi của ROBOT 1: " << endl;
    		visualizePath(arr, robot1.path, fileOut);



			for (auto p : robot2.path) {
        		count2++;
    		}
    		fileOut << "Số ô ROBOT2 đã đi là: "<<count2<<endl;
    		fileOut << "Các vị trí mà ROBOT 2 đã đi là: ";
    		for (auto p : robot2.path) {
        		fileOut << arr[p.first][p.second] << " ";
    		}
    		fileOut << endl;

    		fileOut << "Đường đi của ROBOT 2: " << endl;
    		visualizePath(arr, robot2.path, fileOut);

    // Hiển thị trạng thái của ma trận sau mỗi bước
    		int maxStep = max(robot1.path.size(), robot2.path.size());
    		for (int step = 0; step < maxStep; step++) {
        		vector<pair<int,int>> path1(robot1.path.begin(), robot1.path.begin() + min(step + 1, (int)robot1.path.size()));
        		vector<pair<int,int>> path2(robot2.path.begin(), robot2.path.begin() + min(step + 1, (int)robot2.path.size()));

        		fileOut << "Trạng thái của ma trận sau khi hai ROBOT đã đi xong " << step << " bước:" << endl;
        		fileOut << "ROBOT1"<<endl;
        		visualizePath(arr, path1, fileOut);
        		fileOut << "ROBOT2"<<endl;
        		visualizePath(arr, path2, fileOut);
        		fileOut<<endl<<"----------------------------"<<endl;
    		}	
    		break;
		}
	}
	 
	return 0;
}