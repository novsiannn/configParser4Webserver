/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:11:42 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/04 19:44:10 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_H
# define CONFIGPARSER_H

#include "AllHeaders.hpp"

class ConfigParser 
{
	public:
		ConfigParser();
		~ConfigParser();
		std::string readConfig( std::string path );
		void		skipSpaces(std::string &content);
		void		takeData(std::string line, int i);

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
			std::multimap <std::string, int> _data;
};

void  deleteCommentedLines(std::string &content);

#endif