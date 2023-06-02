class Properties {
	public:
	class Project {
		public:
		const char* NAME = "Project";
		const char* AUTHOR = "Author";
		const char* VERSION = "0.0.0";
		const char* REVISION = "Monday, January 1, 1999 - 12:00 AM";
		const char* GITHUB = "https://github.com/user/project";
	}
	Project;
}
Properties;

void setup() {
	Serial.begin(9600);
	Serial.println(F("Starting\n"));
	delay(1500);

	Serial.println(Properties.Project.NAME);
	Serial.println(Properties.Project.AUTHOR);
	Serial.println(Properties.Project.VERSION);
	Serial.println(Properties.Project.REVISION);
	Serial.println(Properties.Project.GITHUB);
}

void loop() {
}
