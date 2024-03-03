/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:12:20 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/02 17:25:17 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ConfigParser.hpp"
#include "../inc/ConfigFile.hpp"

ConfigParser::ConfigParser(){}

ConfigParser::~ConfigParser(){}

std::string ConfigParser::readConfig( std::string path ){

    ConfigFile  file(path);
    std::string content;

    if (file.getTypePath(file.getPath()) != 1)
		throw ErrorParsing("File is invalid");
	if (file.checkFile(file.getPath(), 4) == -1)
		throw ErrorParsing("File is not accessible");
    
    return path;
}
