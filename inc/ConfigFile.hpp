/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:11:42 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/04 21:29:52 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILE_H
# define CONFIGFILE_H

#include "AllHeaders.hpp"

class ConfigFile 
{
	public:
		ConfigFile();
		~ConfigFile();
        ConfigFile(std::string const path);
        int         getTypePath(std::string path);
        int         isFileExistAndReadable(std::string const path, std::string const index);
        int         checkFile(std::string const path, int mode);
        std::string readFile();
        std::string getPath() const;
        int         checkCurlyBraces(std::string content);
    private:
        std::string _path;
};

#endif