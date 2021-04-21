
class app
{
public:
	app();
	~app();
	void idleForever();
private:
	void setClock();
	void connectwifi();
	ESP8266WebServerSecure* serverHTTP;

	void showPageRoot();
	void showPage_doPowerButton();
	void showPage_doResetButton();
	void showPage_getTargetStatus();

	bool targetPowerLEDState;
};