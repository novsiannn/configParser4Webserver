/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:11:42 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/03 11:40:59 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILE_H
# define CONFIGFILE_H

#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>

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
    private:
        std::string _path;
};

#endif