/*
* atof(): Converts a string to a double with scientific notation support
*/

#include <ctype.h>
#include <stdio.h>

/*
 * atof(): Converts a string to a double with scientific notation
 */

static double myatof(char s[]) {

	double val;
	double power  = 1.0L;
	int    sciexp = 1;
	size_t i;
	int    sign;

	// Eat whitespace
	for (i = 0; isspace(s[i]); i++)
		; // Empty

	// Determine the sign and save its value
	sign = (s[i] == '-') ? -1 : 1;

	// Skip any leading '+' or '-' character (now that sign was dealt with)
	if (s[i] == '+' || s[i] == '-')
		i++;

	// Read the natural number portion
	for (val = 0L; isdigit(s[i]); i++)
		val = 10L * val + (double)(s[i] - '0');

	// Read the fractional portion first skipping the '.' then proceeding if applicable
	if (s[i] == '.') {
		i++;
		for (power = 1L; isdigit(s[i]); i++) {
			val = 10L * val + (double)(s[i] - '0');
			power *= 10L;
		}
	}

	// Save our value so far
	val = sign * val / power;

	// Read the scientific notation if present
	if (toupper(s[i]) == 'E') {
		i++;
		sign = (s[i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;
		for (sciexp = 0; isdigit(s[i]); i++)
			sciexp = 10 * sciexp + (int)(s[i] - '0');
		if (sign == 1)
			while (sciexp-- > 0)
				val *= 10;
		else
			while (sciexp-- > 0)
				val /= 10;
	}

	return val;
}

int main(void) {

	//NOTE: '%.16g' sweeps under the rug the ugliness of floating point conversions.
	//To have some fun, kick it up to '%.52g'
	printf("String \"20\" converted to a double is: %.16g\n", myatof("20"));
	printf("String \"+20\" converted to a double is: %.16g\n", myatof("+20"));
	printf("String \"20.76\" converted to a double is: %.16g\n", myatof("20.76"));
	printf("String \"0\" converted to a double is: %.16g\n", myatof("0"));
	printf("String \"0.12875\" converted to a double is: %.16g\n", myatof("0.12875"));
	printf("String \".6666785\" converted to a double is: %.16g\n", myatof(".6666785"));
	printf("String \"-1234\" converted to a double is: %.16g\n", myatof("-1234"));
	printf("String \"-1234.323\" converted to a double is: %.16g\n", myatof("-1234.323"));
	printf("String \"-43e-2\" converted to a double is: %.16g\n", myatof("43e-2"));
	printf("String \"-.1282e4\" converted to a double is: %.16g\n", myatof("-.1282e4"));
	printf("String \"+67.345e+2\" converted to a double is: %.16g\n", myatof("+67.345e+2"));

	return 0;
}