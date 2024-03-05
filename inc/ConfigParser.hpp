/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:11:42 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/05 20:31:06 by nikitos          ###   ########.fr       */
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
		void		readConfig( std::string path );
		void		skipSpaces(std::string &content);
		int			takeData(std::string line);
		std::string	cutKeyWordBeforeCurly(std::string line);

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
			std::string	_key_word_4_env;
			std::multimap <std::string, std::vector<std::string> > _data;
};

void  deleteCommentedLines(std::string &content);

#endif