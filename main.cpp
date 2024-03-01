/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:10:27 by nikitos           #+#    #+#             */
/*   Updated: 2024/03/01 20:46:54 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ConfigParser.hpp"

int main(int ac, char **av)
{
	ConfigParser conf;
	
	std::string config_name;

	config_name = ac == 1 ? "configs/default.conf" : av[1];
	
	
	if(ac > 2)
		std::cout << "more then 2 args\n";
	return 0;
}