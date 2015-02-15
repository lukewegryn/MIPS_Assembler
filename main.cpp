#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <QStringList>
#include <QString>
#include <QDebug>

#include "exceptions.h"
#include "lexer.h"
#include "util.h"

std::string read_file(const std::string& name) {
  std::ifstream file(name);
  if (!file.is_open()) {
    std::string error = "Could not open file: ";
    error += name;
    throw std::runtime_error(error);
  }
  std::stringstream stream;
  stream << file.rdbuf();
  return std::move(stream.str());
}

struct currentInstruction {
  QString label;
  QString name;
  QStringList token;
} currInstruction;

int main(int argc, char** argv) {
  // Adjusting -- argv[0] is always filename.
  --argc;
  ++argv;

  if (argc == 0) {
    std::cerr << "Need a file" << std::endl;
    return 1;
  }

  for (int i = 0; i < argc; ++i) {
    std::string asmName(argv[i]);

    if (!util::ends_with_subseq(asmName, std::string(".asm"))) {
      std::cerr << "Need a valid file name (that ends in .asm)" << std::endl;
      std::cerr << "(Bad name: " << asmName << ")" << std::endl;
      return 1;
    }

    // 4 is len(".asm")
    auto length = asmName.size() - string_length(".asm");
    std::string baseName(asmName.begin(), asmName.begin() + length);
    std::string objName = baseName + ".obj";
    try {
      auto text = read_file(asmName);
      try {
		auto lexed = lexer::analyze(text);		// Parses the entire file and returns a vector of instructions

		/*for (int i =0; i < (int)lexed.size(); i++){

			if(lexed[i].labels.size() > 0)		// Checking if there is a label in the current instruction
				std::cout << "label = " << lexed[i].labels[0] << "\n";		// Prints the label

			std::cout<< "instruction name = " << lexed[i].name<< "\n";		// Prints the name of instruction

			std::cout << "tokens = ";
			std::vector<lexer::token> tokens = lexed[i].args;
			for(int j=0; j < (int)tokens.size(); j++){       // Prints all the tokens of this instruction like $t1, $t2, $t3
				if (tokens[j].type == lexer::token::Integer)
					std::cout<<tokens[j].integer()<<" ";
				else
					std::cout<<tokens[j].string()<<" ";
			}
			std::cout << "\n\n\n";
		}*/
    for (int i =0; i < (int)lexed.size(); i++){
      currInstruction.token.clear();
      if(lexed[i].labels.size() > 0){		// Checking if there is a label in the current instruction
        currInstruction.label = QString::fromStdString(lexed[i].labels[0]);
        qDebug() << currInstruction.label << "\n";
        }
      currInstruction.name = QString::fromStdString(lexed[i].name);
      std::vector<lexer::token> tokens = lexed[i].args;
      for(int j=0; j < (int)tokens.size(); j++){       // Prints all the tokens of this instruction like $t1, $t2, $t3
        /*if (tokens[j].type == lexer::token::Integer){
          int currInt = tokens[j].integer;
          currInstruction.token.append(QString::number(currInt));
        }*/
          currInstruction.token.append(QString::fromStdString(tokens[j].string()));
      }
      qDebug() << currInstruction.name << "\n";
      //std::cout << currInstruction.token << std:: endl;
      for(int k = 0; k < currInstruction.token.size(); k++){
        qDebug() << currInstruction.token.at(k) << " ";
      }
      std::cout << std::endl;


    }

	  } catch(const bad_asm& e) {
		std::stringstream error;
		error << "Cannot assemble the assembly code at line " << e.line;
		throw std::runtime_error(error.str());
		} catch(const bad_label& e) {
		 std::stringstream error;
		error << "Undefined label " << e.what() << " at line " << e.line;
		throw std::runtime_error(error.str());
		}

    } catch (const std::runtime_error& err) {
      std::cout << err.what() << endl;
      return 1;
    }
  }
  //getchar();
  return 0;
}
