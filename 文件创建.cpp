#include<iostream>
#include<fstream>
#include<filesystem>
#include<vector>
#include<string>
namespace fs = std::filesystem;
void create() {
	fs::path curr_path = fs::current_path();
	std::vector<std::string> files;
	for (int i = 0; i < 50; i++) {
		fs::path file(curr_path);
		std::string temp("seg-" + std::to_string(i + 1) + "-v1-a1");
		temp.append(".ts");
		file.append(temp);
		files.push_back(file.string());
	}
	int cnt = 0;
	for (auto i : files) {
		std::ofstream temp(i);
		temp << cnt + 1 << "\n";
		temp.close();
		cnt++;
	}
}

int main() {
	create();
	system("pause");
	return 0;
}