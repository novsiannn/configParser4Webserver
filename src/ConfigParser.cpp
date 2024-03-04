/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:12:20 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/04 21:32:16 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ConfigParser.hpp"
#include "../inc/ConfigFile.hpp"

ConfigParser::ConfigParser(){}

ConfigParser::~ConfigParser(){}

void deleteCommentedLines(std::string &content)
{
	size_t occ = content.find('#');

	while (occ != std::string::npos)
	{
		size_t occ_end = content.find('\n', occ);
		content.erase(occ, occ_end - occ);
		occ = content.find('#');
	}
}

void ConfigParser::skipSpaces(std::string &content)
{
  size_t i = 0;

  while(content[i] && isspace(content[i]))
    i++;
  if(content[i] == '\0')
    throw ErrorParsing("All lines in file are commented or all lines are spaces");
  content = content.substr(i);
  i = content.length() - 1;

  while(i > 0 && isspace(content[i]))
    i--;
  content = content.substr(0, i + 1);
}

void	ConfigParser::takeData(std::string line, int i)
{
	// std::cout << line;
	this->_data.insert(std::make_pair(line, i));
}

int	ConfigFile::checkCurlyBraces( std::string content )
{
	int opening_brace = 0;
	int closing_brace = 0;
	int i = 0;

	while(content[i] != 0)
	{
		if (content[i] == '{')
			++opening_brace;
		else if (content[i] == '}')
			++closing_brace;
		i++;
	}
	if(opening_brace == closing_brace)
		return 1;
	else
		return 0;
}

std::string ConfigParser::readConfig( std::string path )
{

    ConfigFile		fileToCheck(path);
	std::string		line;
	std::string		content;
	std::ifstream	file_toTakeData(path);

    if (fileToCheck.getTypePath(fileToCheck.getPath()) != 1)
		  throw ErrorParsing("File is invalid");
    if (fileToCheck.checkFile(fileToCheck.getPath(), 4) == -1)
		  throw ErrorParsing("File is not accessible");
	content = fileToCheck.readFile();
    if(content.empty())
    	throw ErrorParsing("File is empty");
	deleteCommentedLines(content);
	if (!fileToCheck.checkCurlyBraces( content ))
		throw ErrorParsing("Curly Braces are not closed");

	// if (file_toTakeData.is_open()) 
	// {
	// 	int i = 0;
    // 	while (getline(file_toTakeData, line, ';'))
    //     {
	// 		i++;
	// 		this->takeData(line, i);
	// 		// if (i > 3 )
	// 		// 	break;
	// 	}
	// 	std::multimap <std::string, int>::iterator it;
	// 	for(it = _data.begin(); it != _data.end(); it++)
	// 	{
	// 		std::cout << it->second <<" element in map -> " << it->first << std::endl;
	// 	}
    // }
	

	// file.takeData(file);

    // skipSpaces(content);
    return path;
}
