/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:12:20 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/05 00:47:53 by nikitos          ###   ########.fr       */
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

int checkStringEmpty(std::string line)
{
	int k = 0;

	while (isspace(line[k]) && line[k] != '\0' && line[k] != '\n')
		k++;
	if (line[k] == '\0' || line[k] == '\n')
		return 1;
	else
		return 0;
}

void	ConfigParser::takeData(std::string line, int i)
{
	// (void)line;
	(void)i;
	int k = 0;
	int j = 0;
	size_t found_semicolon = line.find(";");
	size_t found_curly_brace = line.find("{");
	size_t found_hash = line.find("#");
	
	if (found_hash != std::string::npos)
	{
		size_t end_line = line.find('\n', found_hash);
		line.erase(found_hash, end_line - found_hash + 1);
		if (checkStringEmpty(line))
			return ;
	}
	// std::cout << "["<< line << "]" << std::endl;
	if (found_semicolon != std::string::npos && found_curly_brace == std::string::npos)
	{
		while (isalnum(line[k]) || line[k] == '_')
			k++;
		while(isspace(line[k]) && line[k] != '\0' && line[k] != '\n')
			k++;
		if(!isalnum(line[k]))
			throw ErrorParsing("Incorrect config file");
		j = k;
		while (line[k] != ';' && line[k] != '\n' && line[k] != '\0')
			k++;
		std::cout << line.substr(j,k) << std::endl;
		// std::cout << line.substr(0,k) << std::endl;
		
		// _data.insert(make_pair(line.substr(0,k), 1));
	}
	// std::cout << line;
	// this->_data.insert(std::make_pair(line, i));
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

	if (file_toTakeData.is_open()) 
	{
		int i = 0;
    	while (getline(file_toTakeData, line))
        {
			i++;
			this->takeData(line, i);
			// if( i > 3)
			// 	break ;
		}
		std::multimap <std::string, std::vector<std::string> >::iterator it;
		std::vector<std::string>::iterator it_vec;
		for(it = _data.begin(); it != _data.end(); it++)
		{
			// std::cout << "Element in map key   ->     " << it->first << std::endl;
			for (it_vec = it->second.begin(); it_vec != it->second.end(); it_vec++)
			{
				// std::cout << " Element in map value ->   " << *it_vec;  
			}
			// std::cout << '\n';
		}
    }
	
	// skipSpaces(content);
	// file.takeData(file);

    return path;
}
