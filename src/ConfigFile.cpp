/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:10:27 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/02 14:44:10 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ConfigFile.hpp"


ConfigFile::ConfigFile() : _path("default"){}
ConfigFile::~ConfigFile(){}

ConfigFile::ConfigFile( std::string path ) : _path(path){}

int ConfigFile::getTypePath( std::string path )
{
    struct stat buffer;
    int         res;

    res = stat(path.c_str(), &buffer);
    if (res == 0)
	{
		if (buffer.st_mode & S_IFREG) // Buffer.st_mode is member func from stat struct, that returns info about file mode and permissions of file. IFREG checks file( readular file)
			return (1);
		else if (buffer.st_mode & S_IFDIR) // S_IFDIR checks if it directory or not.
			return (2);
		else
			return (3);
	}
	else
		return (-1);
}

int	ConfigFile::checkFile(std::string const path, int mode)
{
	return (access(path.c_str(), mode));
}

std::string ConfigFile::getPath() const
{
    return ( this->_path );
}

int ConfigFile::isFileExistAndReadable(std::string const path, std::string const index)
{
	if (getTypePath(index) == 1 && checkFile(index, 4) == 0)
		return (0);
	if (getTypePath(path + index) == 1 && checkFile(path + index, 4) == 0)
		return (0);
	return (-1);
}

std::string ConfigFile::readFile( std::string path )
{
	
	if (path.empty() || path.length() == 0)
		return (NULL);
	std::ifstream config_file(path.c_str());
	if (!config_file || !config_file.is_open())
		return (NULL);
	
	std::stringstream stream_binding;
	stream_binding << config_file.rdbuf();
	return (stream_binding.str());
}