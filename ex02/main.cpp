/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 23:43:47 by rhiguita          #+#    #+#             */
/*   Updated: 2026/04/29 23:43:48 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "functions.hpp"

int main() {
	std::srand(std::time(NULL));

	for (int i = 0; i < 5; i++) {
		std::cout << "--- Test " << i + 1 << " ---" << std::endl;
		Base* obj = generate();

		std::cout << "identify(ptr): ";
		identify(obj);

		std::cout << "identify(ref): ";
		identify(*obj);

		delete obj;
		std::cout << std::endl;
	}

	return 0;
}
