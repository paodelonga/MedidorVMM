class Properties {
	public:
	class Project {
		public:
		const char* Name = "Project Name"ç
		const char* Author = "Author Name";
		const char* Version = "0.0.0";
		const char* Revision = "Segunda-Feira, 1 de Janeiro de 1999 - 00:00 AM";
		const char* Github = "https://github.com/user/projectName";
	}
	Project;
}
Properties;

void setup() {
	Serial.begin(9600);

	Serial.println(Properties.Project.Author);
	Serial.println(Properties.Project.Version);
	Serial.println(Properties.Project.Rev);
	Serial.println(Properties.Project.Github);
}

void loop() {
}