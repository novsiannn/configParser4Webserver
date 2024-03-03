/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:10:27 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/02 16:20:28 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ConfigParser.hpp"
#include "inc/ConfigFile.hpp"

int main(int ac, char **av)
{
	ConfigParser	conf;
	ConfigFile		test;
	
	std::string config_name;
	std::string read_file;

	config_name = ac == 1 ? "cfg/default.conf" : av[1];

	try
	{
		conf.readConfig(config_name);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


	if(ac > 2)
		std::cout << "more then 2 args\n";
	
	return 0;
}