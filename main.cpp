#include <cmath>
#include <iostream>
#include <charconv>
#include <optional>
#include <string>
#include <string_view>
#include "main.h"

std::string get_user_input(std::string prompt)
{
	std::string input_str{};
	std::cout << prompt;

	std::getline(std::cin, input_str);

	return input_str;
}


std::optional<float> get_amount(std::string_view amount)
{
	float value{};
	auto end{ amount.data() + amount.length() };
	const auto format = std::chars_format::general;

	if (std::from_chars(amount.data(), amount.data() + amount.size(), value, format).ptr != end)
		return {};
	
	if (value <= 0.0f)
		return {};

	return value;
}

void calculate_total(float& tip, float bill_amount, float tip_rate, float& total)
{
	tip = std::roundf(bill_amount * (tip_rate / 100.0f));
	total = bill_amount + tip;
}

void display_results(std::string& tip_out_message, std::string& total_out_message, float tip, float total)
{
	std::cout << tip_out_message << tip << '\n';
	std::cout << total_out_message << total << '\n';
}

void input_amount(std::string bill_amount_prompt, std::string input_error_message, float& amount)
{
	while (true)
	{
		if (auto extracted{ get_amount(get_user_input(bill_amount_prompt)) })
		{
			amount = extracted.value();
			break;
		}
		std::cout << input_error_message;
	}	
}

int main()
{
	float bill_amount = 0.0f;
	float tip = 0.0f;
	float tip_rate = 0.0f;
	float total = 0.0f;

	std::string bill_amount_prompt{ "Enter the bill amount: " };
	std::string tip_rate_prompt{ "Enter the tip rate: " };
	std::string tip_out_message{ "Tip: $" };
	std::string total_out_message{ "Total: $" };
	std::string input_error_message{ "Please enter a valid number\n" };
	
	input_amount(bill_amount_prompt, input_error_message, bill_amount);
	input_amount(tip_rate_prompt, input_error_message, tip_rate);

	calculate_total(tip, bill_amount, tip_rate, total);
	display_results(tip_out_message, total_out_message, tip, total);

	return 0;
}
