/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:12:20 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/03 14:51:15 by novsiann         ###   ########.fr       */
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

void  ConfigParser::splitServers(std::string &content)
{
  if(content.find("server", 0) == std::string::npos) 
    throw ErrorParsing("Server did not find");
}

std::string ConfigParser::readConfig( std::string path )
{

    ConfigFile  file(path);
    std::string content;

    if (file.getTypePath(file.getPath()) != 1)
		  throw ErrorParsing("File is invalid");
    if (file.checkFile(file.getPath(), 4) == -1)
		  throw ErrorParsing("File is not accessible");
    content = file.readFile();
    if(content.empty())
      throw ErrorParsing("File is empty");
    deleteCommentedLines(content);
    skipSpaces(content);
    splitServers(content);
  
    // std::cout << content << std::endl;
    
    
    return path;
}
