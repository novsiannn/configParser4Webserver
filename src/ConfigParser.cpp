/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:12:20 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/05 12:31:18 by nikitos          ###   ########.fr       */
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

int	ConfigParser::takeData(std::string line)
{
	int k = 0;
	int j = 0;
	size_t found_semicolon = line.find(";");
	size_t foundOpeningCurlyBrace = line.find("{");
	size_t found_hash = line.find("#");
	std::vector<std::string> tmp;
	std::string elem;

	if (found_hash != std::string::npos)
	{
		size_t end_line = line.find('\n', found_hash);
		line.erase(found_hash, end_line - found_hash + 1);
		if (checkStringEmpty(line))
			return 0;
	}
	if (found_semicolon != std::string::npos && foundOpeningCurlyBrace == std::string::npos)
	{
		std::string key_for_line;
		while(isspace(line[k]))
			k++;
		j = k;
		while (isalnum(line[k]) || line[k] == '_')
			k++;
		key_for_line = line.substr(j,k);
		while(isspace(line[k]))
			k++;
		if(!isalnum(line[k]))
			throw ErrorParsing("Incorrect config file");
		j = k;
		while (line[k] != ';' && line[k] != '\n' && line[k] != '\0')
			k++;

		std::string val_for_line = line.substr(j,k);
	
		std::stringstream ss(val_for_line);
		while(ss >> elem)
			tmp.push_back(elem);
		_data.insert(make_pair(key_for_line, tmp));
	}
	return 0;
}

std::string	ConfigParser::cutKeyWordBeforeCurly(std::string line)
{
	int k = 0;
	int j = 0;
	while(isspace(line[j]))
		j++;
	while (line[k] != '\0' && line[k] != '\n' && line[k] != '{')
			k++;
	if (line[k] == '\n' || line[k] == '\0')
    	return line.substr(j);
	else
    	return line.substr(j, k - j);
}

std::string ConfigParser::readConfig( std::string path )
{

    ConfigFile		fileToCheck(path);
	std::string		line;
	std::string		content;
	std::ifstream	file_toTakeData(path);
	size_t foundOpeningCurlyBrace;
	size_t foundClosedCurlyBrace;

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
		int scope = 0;
    	while (getline(file_toTakeData, line))
        {
			foundOpeningCurlyBrace = line.find("{");
			foundClosedCurlyBrace = line.find("}");
			// int k = 0;
			if ((foundOpeningCurlyBrace != std::string::npos && foundClosedCurlyBrace == std::string::npos ) || scope > 0)
			{
				if (scope == 0)
					_keyForMainScope = cutKeyWordBeforeCurly(line);
				if (foundOpeningCurlyBrace != std::string::npos)
					scope++;
				while(scope != 0)
				{
					std::string remainingContent;
					std::string elem;
					char c;
            		while (file_toTakeData.get(c) && scope != 0) 
					{
						if (c == '{')
							scope++;
						else if(c == '}')
							scope--;
                		remainingContent += c;
            		}
					std::vector<std::string> tmp;
					std::stringstream ss(remainingContent);
					while(ss >> elem)
						tmp.push_back(elem);
					_data.insert(make_pair(_keyForMainScope, tmp));
					continue;
				}
			}
			this->takeData(line);
		}
		
		std::multimap <std::string, std::vector<std::string> >::iterator it;
		std::vector<std::string>::iterator it_vec;
		for(it = _data.begin(); it != _data.end(); it++)
		{
			std::cout << "Element in map key   -> " << it->first << std::endl;
			for (it_vec = it->second.begin(); it_vec != it->second.end(); it_vec++)
			{
				std::cout << "Element in map value -> " << *it_vec << std::endl;  
			}
			std::cout << "NEXT PAIR" << std::endl;
		}
    }
	
	// skipSpaces(content);
	// file.takeData(file);

    return path;
}
