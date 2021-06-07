void DetectorInit(void);
enum DetectorState{ACTIVE, INACTIVE};
enum DetectorState eReadDetector();
enum ServoState {CALLIB, IDLE, IN_PROGRESS};
enum ServoCommand {CALLIB_COM, GOTO, WAIT};

struct Servo{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};

struct ServoControl{
	enum ServoCommand eCommand;
	unsigned int uiDesiredPosition;
	unsigned int uiNumberOfTicks;
};

void Automat(void);
void ServoCallib(void);
void ServoInit();
void ServoGoTo(unsigned int uiPosition);
void ServoRun(void *pvParameters);
void ServoWait(unsigned int uiNumberOfTicks);
