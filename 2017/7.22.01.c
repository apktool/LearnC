#include<stdio.h>

#define BCD_TO_BIN(val) ((val)=((val)&15) + ((val)>>4)*10)
#define MINUTE 60            // 1分钟有多少秒
#define HOUR (60*MINUTE)     // 1小时有多少妙
#define DAY (24*HOUR)        // 1天有多少秒
#define YEAR (365*DAY)       // 1年有多少秒

// 2017-07-22 00:29:58
// 1970-00-00 00:00:00

struct tm{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

static int month[12] = {
	0,
	DAY*(31),
	DAY*(31+29),
	DAY*(31+29+31),
	DAY*(31+29+31+30),
	DAY*(31+29+31+30+31),
	DAY*(31+29+31+30+31+30),
	DAY*(31+29+31+30+31+30+31),
	DAY*(31+29+31+30+31+30+31+31),
	DAY*(31+29+31+30+31+30+31+31+30),
	DAY*(31+29+31+30+31+30+31+31+30+31),
	DAY*(31+29+31+30+31+30+31+31+30+31+30)
};

long kernel_mktime(struct tm * tm)
{
	long res;
	int year;
	/**
	 * @Synopsis  计算当前时间到1970年有多少年
	 */
	if (tm->tm_year >= 70)
		year = tm->tm_year - 70;
	else
		year = tm->tm_year + 100 -70;        // (2017-1970)
	/**
	 * @Synopsis  YEAR*year: 计算当前年到1970年有多少秒
	 * @Synopsis  Day*((yeaer+1)/4): 计算当前时间到1970年有多少个润年
	 *            这里因为包含今年，因此必须+1
	 */
	//已经对润年里面的润二月进行修正
	res = YEAR*year + DAY*((year+1)/4);      // (2017-1970)*YEAR+12*DAY
	/**
	 * @Synopsis  计算当前月到年初共多少秒
	 */
	res += month[tm->tm_mon];                // (2017-1970)*YEAR+12*DAY+month[6]
	/**
	 * @Synopsis 当前年的二月如果不是闰月，则对前面定义的29天的二月进行修正
	 */
	if (tm->tm_mon>1 && ((year+2)%4))
		res -= DAY;                          // ((2017-1970)*YEAR+12*DAY+month[6])-1*DAY
	/**
	 * @Synopsis  计算当前天到月初共多少秒
	 */
	res += DAY*(tm->tm_mday-1);              // (((2017-1970)*YEAR+12*DAY+month[6])-1*DAY)+22*DAY
	/**
	 * @Synopsis  计算当前小时到0点共多少秒
	 */
	res += HOUR*tm->tm_hour;                 // (((2017-1970)*YEAR+12*DAY+month[6])-1*DAY)+22*DAY+00*HOUR
	/**
	 * @Synopsis  计算当前分钟到整点时共多少秒
	 */
	res += MINUTE*tm->tm_min;                // (((2017-1970)*YEAR+12*DAY+month[6])-1*DAY)+22*DAY+00*HOUR+29*MINUTE
	/**
	 * @Synopsis  计算当前秒到整点分共多少秒
	 */
	res += tm->tm_sec;                       // (((2017-1970)*YEAR+12*DAY+month[6])-1*DAY)+22*DAY+00*HOUR+29*MINUTE+58*MINUTE
	return res;
}

int main(int argc, char* argv[]){
	struct tm time;

	/* These values come from CMOS */
	time.tm_sec = 84;
	time.tm_min = 41;
	time.tm_hour = 0;
	time.tm_mday = 34;
	time.tm_mon = 7;
	time.tm_year = 23;
	time.tm_wday = -484442112;
	time.tm_yday = 753824;
	time.tm_isdst = 104167;

	BCD_TO_BIN(time.tm_sec);
	BCD_TO_BIN(time.tm_min);
	BCD_TO_BIN(time.tm_hour);
	BCD_TO_BIN(time.tm_mday);
	BCD_TO_BIN(time.tm_mon);
	BCD_TO_BIN(time.tm_year);
	time.tm_mon--;

	long startup_time = 0;
	startup_time = kernel_mktime(&time);
	printf("%ld\n", startup_time);

	return 0;
}
