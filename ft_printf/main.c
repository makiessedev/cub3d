#include "../libft/libft.h"
#include <stdio.h>

char	ft_puthex(unsigned int n)
{
	int		count;
	char	*hex_digits;
	char	digit[25];

	hex_digits = "0123456789ABCDEF";
	if (n == 0)
		return ('0');
	count = 0;
	while (n != 0)
	{
		digit[count++] = hex_digits[n % 16];
		n /= 16;
	}
	return (digit);
}

int main(void) {
  printf("%i", ft_puthex(255));
  return (0);
}
