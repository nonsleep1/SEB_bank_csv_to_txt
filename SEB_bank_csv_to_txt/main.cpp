#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <string>

#include <fcntl.h>
#include <io.h>
#include <sstream>
#include <ctime>

#include <locale>


bool replace(std::string& str, const std::string& from, const std::string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

std::string trim(const std::string& line, const char& fromthistodelete)
{
	std::string newline = "";
	std::size_t pos = line.find(fromthistodelete);
	if (pos != -1)
	{
		newline = line.substr(0, pos);
	}
	else
	{
		//std::cout << "Klaida!";
	}
	return newline;
}

std::string ReturnFileNameWithDate(int option)
{
	try
	{
		std::string date = "";
		time_t now = time(0);
		struct tm newtime;
		struct tm newtimeminusonemonth;


		localtime_s(&newtime, &now);

		/*std::cout << "Year:" << 1900 + newtime.tm_year << std::endl;
		std::cout << "Month: " << 1 + newtime.tm_mon << std::endl;
		std::cout << "Day: " << newtime.tm_mday << std::endl;
		std::cout << "Time: " << 1 + newtime.tm_hour << ":";
		std::cout << 1 + newtime.tm_min << ":";
		std::cout << 1 + newtime.tm_sec << std::endl;

		std::cout << "seb_" << 1900 + newtime.tm_year << newtime.tm_mon << ".txt" << std::endl;*/

		char mbstr[100];

		if (std::strftime(mbstr, sizeof(mbstr), "%Y%m%u", &newtime)) {
			//std::cout << " MBSTR: " << mbstr << '\n';
			newtimeminusonemonth = newtime;
		}
		switch (option)
		{
		default:
			std::cout << "Nepasirinktas option\n";
			return "Error";
			break;

		case 1:
			newtimeminusonemonth.tm_mon = newtimeminusonemonth.tm_mon - 1;
			date = "seb" + std::string(mbstr) + ".txt";

			return date;
		
		}

		//std::cout << "TV_" << mbstr << ".txt" << std::endl;


	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
}

int main(int argc, char* argv[]) {
	std::cout << "Parameters: " << argc << "\n";
	//std::cout << argv[1] << "\n";
	if (argc > 0)
	{
		try {
			std::ifstream mycsv("testas3.csv");
			//std::ifstream mycsv(argv[1]);
			std::ofstream remade(ReturnFileNameWithDate(1));
			std::vector<std::string>parsedline;
			std::string line = "";
			std::string wstringas = "";
			std::size_t found = 0;
			int countas = 0;
			int lineNum = 0;
			if (mycsv.is_open())
			{
				std::cout << "File opened!\n";
				while (std::getline(mycsv, line))
				{
					
					lineNum++;
					//std::cout << lineNum << "\n";
					//if (lineNum < 2)
					//{
					//	//continue;
					//}
					if(lineNum > 2)
					{
						std::stringstream wstr(line);
						while (std::getline(wstr, wstringas, ';'))
						{
							parsedline.push_back(wstringas);
						}
						
						if (parsedline.size() > 14) {
							//found = parsedline[9].find("##");
							//std::cout << "Number of found: " << found << "\n";
							if((parsedline[9].find('#')) < parsedline[9].length())
							{
								std::cout << parsedline[1] << " " << parsedline[3] << " " << parsedline[9] << "\n";
								remade << parsedline[1] << "\t" << parsedline[3] << "\t" << parsedline[9] << "\n";

								//std::cout << "kazkaz:  " <<parsedline[1] << "\n";
								parsedline.clear();

								/*found = parsedline[9].find("#");
								if (found != std::string::npos) {
									std::cout << "first 'needle' found at: " << found << '\n';
									countas++;
									replace(parsedline[15], "LT-\r", "LT-");
								}*/
							}
							//found = 0;
							/*	parsedline[4] = trim(parsedline[4], '.');
								parsedline[6] = trim(parsedline[6], '.');
								parsedline[8] = trim(parsedline[8], '.');
								parsedline[10] = trim(parsedline[10], '.');*/
							
							
						}
					}
						
					
				}
				std::cout <<"npos =  "<<std::string::npos << "\n";
			}
			else
			{
				std::cout << "FILE DIDN'T FOUND!";
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		
	}
	else 
	{
		std::cout << "Too many or to little arguments!";
	}

	return 0;
}