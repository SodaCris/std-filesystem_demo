#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<vector>
namespace fs = std::filesystem;

void rename() {
	fs::path curr_path = fs::current_path();
	for (auto i : fs::directory_iterator(curr_path)) {
		fs::path ii(i);
		if (!fs::is_regular_file(ii)) {
			continue;
		}
		std::string filename = ii.filename().string();
		if (filename.substr(filename.size() - 3, std::string::npos) != ".ts") {
			continue;
		}
		std::vector<std::string> tokens;
		std::string delim = "-";

		//将文件名以"-"分开，存到tokens里
		size_t last = 0, next = 0;
		while ((next = filename.find(delim, last)) != std::string::npos) {
			tokens.push_back(filename.substr(last, next - last));
			last = next + 1;
		}
		tokens.push_back(filename.substr(last));
		int n = std::stoi(tokens[1]);
		char buf[20];
		std::snprintf(buf, sizeof(buf), "%03d", n);
		std::string seq(buf);
		tokens[1] = seq;
		std::string newname = "";
		for (int j = 0; j < tokens.size(); j++) {
			newname += tokens[j];
			if (j != tokens.size() - 1) {
				newname += "-";
			}
		}
		std::cout << "new name: " << newname << std::endl;
		fs::path temp(curr_path);
		temp.append(newname);
		fs::rename(ii, temp);
	}
}

int main() {
	rename();
	system("pause");
	return 0;
}