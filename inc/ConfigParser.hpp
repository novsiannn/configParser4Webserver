/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:11:42 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/02 16:20:34 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_H
# define CONFIGPARSER_H

#include <iostream>

class ConfigParser 
{
	public:
		ConfigParser();
		~ConfigParser();
		std::string readConfig( std::string path );

		class ErrorParsing : public std::exception
		{
			private:
				std::string _message;
			public:
				ErrorParsing(std::string message) throw()
				{
					_message = "CONFIG PARSER ERROR: " + message;
				}
				virtual const char* what() const throw()
				{
					return (_message.c_str());
				}
				virtual ~ErrorParsing() throw() {}
		};
		private:
			std::string _message;
};

#endif