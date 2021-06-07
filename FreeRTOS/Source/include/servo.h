void DetectorInit(void);
enum DetectorState{ACTIVE, INACTIVE};
enum DetectorState eReadDetector();
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo 
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};

void Automat(void);
void ServoCallib(void);
void ServoInit();
void ServoGoTo(unsigned int uiPosition);
void ServoRun(void *pvParameters);
