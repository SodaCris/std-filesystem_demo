#include<iostream>
#include<fstream>
#include<filesystem>
#include<vector>
#include<string>
namespace fs = std::filesystem;

void concat() {
	std::vector<std::string> files;
	fs::path curr_path = fs::current_path();
	for (auto i : fs::directory_iterator(curr_path)) {
		fs::path ii(i);
		if (!fs::is_regular_file(ii)) {
			continue;
		}
		std::string iname = ii.filename().string();
		if (iname.substr(iname.size() - 3, std::string::npos) == ".ts") {
			std::cout << "find file: " << iname << std::endl;
			files.push_back(iname);
		}
	}
	fs::path out_path(curr_path);
	out_path.append("out.ts");
	std::ofstream outfile(out_path);
	for (auto i : files) {
		std::ifstream temp(i, std::ios_base::binary);
		outfile << temp.rdbuf();
		temp.close();
	}
	outfile.close();
	for (auto i : files) {
		fs::path temp(i);
		fs::remove(temp);
	}
}

int main() {
	//create();
	concat();
	system("pause");
	return 0;
}