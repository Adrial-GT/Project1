���Զ�����ϵͳ����ʾ2D��ģ�漰��������ܣ����������������·��棺

1. **2D��ģ��Ⱦ**��Ϊ���ڽ�������ʾ����������Ҫ��д��Ⱦ���룬��2D��ģ���Ƶ���Ļ�ϡ��������Ҫʹ��ͼ�ο����������2Dͼ�Ρ�

2. **������̬����**�������Զ������Ľ��Ⱥ�״̬����������Ҫ����2D��ģ����̬�����������̵�ת�򡢳��ֵ�ת���ͳ�������б�ȣ��Է�ӳʵ�ʲ�����

3. **���Ŷ���**��������ƻ��ڽ�������ʾ���ŵ�״̬��������رգ�������Ҫʵ�ֳ��ŵĶ���Ч����������漰�����ŵ�ƽ�ơ���ת���뵭��Ч����

4. **������������ʾ**��2D��ģ����ʾͨ����Ҫ�������������ݣ���ȷ�������ڽ����ϵ�λ�ú�״̬��ʵ�ʻ���һ�¡�����ܰ������Գ������������糬�����������������ݣ����ڱ�����ײ��

5. **������ť**����������Ҫ�ڽ�������Ӳ�����ť���������û�ִ���ض��Ĳ�����������ͣ�����̡��л�����״̬��ȡ��ͣ���ȡ�

6. **����״̬��Ϣ**����ʾ������״̬��Ϣ�����ٶȡ�ת��Ƕȡ�����λ�õȣ��Ա��û����Ը��ٳ����Ĳ�����

7. **��������**�������Ҫʵ��ƽ���Ķ���Ч��������Ҫ��д�������ƴ��룬������ֵ��ʱ�䲽������Ⱦѭ���ȡ�

8. **�û����潻��**��Ϊ�����û�����������Ҫ�����û����룬���������϶������ŵ����ƣ��Լ���Ӧ���¼�����

9. **�����״̬����**��Ϊ���ṩ���õ��û����飬����Ҫʵ�ִ������״̬�����Դ�����ܳ��ֵ�������쳣�����

10. **�����Ż�**�����ڽϸ��ӵ�2D��ģ�Ͷ���Ч������������Ҫ���������Ż�����ȷ���ڸ���Ӳ���϶����������С�

��Щ������Ҫ�漰ͼ����Ⱦ���������ơ��û�������ƺͽ��������ݴ���ȶ������Ŀ������ܡ�ͬʱ����Щ���ܵĸ��ӳ̶Ⱥ�ʵ�ַ�ʽ���������ľ��������Ŀ����仯��



class CarModel {
public:
    // ���캯����������Ⱦ����Ĳ���
    CarModel(/* ������Ⱦ����Ĳ��� */) {
        // ��ʼ����Ⱦ��ص����ݣ���������������ö������ݵ�
        // ��ʼ������״̬����������
    }

    // ��ָ������
    void OpenDoor(const std::string& doorName) {
        // ����doorNameִ����Ӧ���ŵĿ�������
    }

    // �ر�ָ������
    void CloseDoor(const std::string& doorName) {
        // ����doorNameִ����Ӧ���ŵĹرն���
    }

    // �����г���
    void OpenAllDoors() {
        // ִ�����г��ŵĿ�������
    }

    // �ر����г���
    void CloseAllDoors() {
        // ִ�����г��ŵĹرն���
    }

    // �򿪳���
    void OpenHood() {
        // ִ�г��ǵĿ�������
    }

    // �رճ���
    void CloseHood() {
        // ִ�г��ǵĹرն���
    }

    // �򿪺���
    void OpenTrunk() {
        // ִ�к���Ŀ�������
    }

    // �رպ���
    void CloseTrunk() {
        // ִ�к���Ĺرն���
    }

    // ���Ƴ���״̬������/�رգ�
    void ToggleLights() {
        // ִ�г���״̬���л�
    }

    // ���³�ģ��״̬������λ�á��Ƕȵ�
    void Update(float deltaTime) {
        // ��������³�ģ��״̬���������ڶ���Ч��
    }

    // ��Ⱦ��ģ
    void Render() {
        // ������ִ�г�ģ����Ⱦ�����Ƴ����ͳ��ŵ�
    }

private:
    // ��Ա�������ڴ洢����״̬��λ�á���̬����Ϣ
};


class CarModel {
public:
    // ���캯����������Ⱦ����Ĳ������Լ������ĳ�ʼ״̬
    CarModel(/* ��Ⱦ���� */, const std::string& modelName) {
        // ��ʼ����Ⱦ��ص����ݣ���������������ö������ݵ�
        // ��ʼ������״̬���������š����ǡ����Ƶ�
    }

    // ���س���
    void ToggleDoor(const std::string& doorName) {
        // ����doorNameִ����Ӧ���ŵĿ��ض��������Դ���"front_left", "front_right", "rear_left", "rear_right"���ŵ�����
    }

    // ���س���
    void ToggleHood() {
        // ִ�г��ǵĿ��ض���
    }

    // ���غ���
    void ToggleTrunk() {
        // ִ�к���Ŀ��ض���
    }

    // ���Ƴ���״̬������/�رգ�
    void ToggleLights() {
        // ִ�г���״̬���л�
    }

    // ���³�ģ��״̬������λ�á��Ƕȵ�
    void Update(float deltaTime) {
        // ��������³�ģ��״̬���������ڶ���Ч��
    }

    // ��Ⱦ��ģ
    void Render() {
        // ������ִ�г�ģ����Ⱦ�����Ƴ����ͳ��ŵ�
    }

private:
    // ��Ա�������ڴ洢����״̬��λ�á���̬����Ϣ
};


// ʵ����CarModel�࣬������Ⱦ�����ͳ���ģ�͵�����
CarModel car(/* ��Ⱦ���� */, "car_model.obj");

// ����ǰ����
car.ToggleDoor("front_left");

// �رճ���
car.ToggleHood();

// �򿪺���
car.ToggleTrunk();

// �л�����״̬
car.ToggleLights();

// ���³�ģ״̬����Ⱦ
car.Update(deltaTime);
car.Render();


#include <iostream>
#include <vector>

class CarModel {
public:
    CarModel(const std::string& modelName) {
        // ��ʼ������״̬���������š����ǡ����Ƶ�
        for (int i = 0; i < NUM_DOORS; i++) {
            doors.push_back(false); // ��ʼ�����г���Ϊ�ر�״̬
        }
        hoodOpen = false;
        trunkOpen = false;
        lightsOn = false;

        // ���س���ģ�ͺ�������Ⱦ�������
        std::cout << "Loaded model: " << modelName << std::endl;
    }

    // ���س��ţ����복��״̬����
    void ToggleDoors(const std::vector<bool>& doorStates) {
        if (doorStates.size() != NUM_DOORS) {
            std::cout << "Invalid door state array size" << std::endl;
            return;
        }

        for (int i = 0; i < NUM_DOORS; i++) {
            doors[i] = doorStates[i];
        }
    }

    // ���Ƴ���״̬������/�رգ�
    void ToggleHood() {
        hoodOpen = !hoodOpen; // �л�����״̬
    }

    // ���ƺ���״̬������/�رգ�
    void ToggleTrunk() {
        trunkOpen = !trunkOpen; // �л�����״̬
    }

    // ���Ƴ���״̬������/�رգ�
    void ToggleLights() {
        lightsOn = !lightsOn; // �л�����״̬
    }

    // ���³�ģ��״̬������λ�á��Ƕȵ�
    void Update(float deltaTime) {
        // ��������³�ģ��״̬���������ڶ���Ч��
    }

    // ��Ⱦ��ģ
    void Render() {
        // ������ִ�г�ģ����Ⱦ�����Ƴ����ͳ��ŵ�
        std::cout << "Rendering car model" << std::endl;
    }

private:
    static const int NUM_DOORS = 4; // ������4������

    std::vector<bool> doors;
    bool hoodOpen;
    bool trunkOpen;
    bool lightsOn;
};

int main() {
    // ʵ����CarModel�࣬���복��ģ�͵�����
    CarModel car("car_model.obj");

    // ���س��ţ�ʹ��״̬�����ʾ����״̬
    std::vector<bool> doorStates = {true, false, true, false}; // ���磺�򿪵�1�͵�3�����ţ��ر����೵��
    car.ToggleDoors(doorStates);

    // ���Ƴ���״̬
    car.ToggleHood();

    // ���ƺ���״̬
    car.ToggleTrunk();

    // ���Ƴ���״̬
    car.ToggleLights();

    // ���³�ģ״̬����Ⱦ
    car.Update(0.1f);
    car.Render();

    return 0;
}



-------------------------------------------
|                CarModel                 |
-------------------------------------------
| - doors: std::vector<bool>              |
| - hoodOpen: bool                        |
| - trunkOpen: bool                       |
| - lightsOn: bool                        |
-------------------------------------------
| + CarModel(modelName: std::string)     |
| + ToggleDoors(doorStates: std::vector<bool>) |
| + ToggleHood()                          |
| + ToggleTrunk()                         |
| + ToggleLights()                        |
| + Update(deltaTime: float)             |
| + Render()                              |
-------------------------------------------



����������£����������һ�� CarModel �࣬������������������ֱ����ڳ�ģ��Ⱦ����ȡ����ͳ���ͼƬ�Լ����Ƴ��ź�ǰ��ǿ��ء�������Ҫ��������������������ͼƬ��Ⱦ�ͳ��ſ��ض����������Ǿ���Ĵ������Ӧ�� UML ��ͼ��

���ȣ����� CarModel ��Ĵ��룺

#include <iostream>
#include <vector>
#include <string>

// ǰ������������
class ImageRenderer;
class DoorAnimator;

class CarModel {
public:
    CarModel(const std::string& modelName) {
        // ��ʼ������״̬����������
        // ���س���ģ�ͺ���Ⱦ�������
        std::cout << "Loaded model: " << modelName << std::endl;

        // ��ʼ��������
        imageRenderer = new ImageRenderer();
        doorAnimator = new DoorAnimator();
    }

    ~CarModel() {
        // ��������
        delete imageRenderer;
        delete doorAnimator;
    }

    // ��Ⱦ��ģ�����복��λ�ã����ݳ���λ�ü�������������λ��
    void Render(const glm::vec3& carBodyPosition) {
        // ���ݳ���λ�ü����������������糵�ţ���λ��
        // ���ø��������Ⱦ����
        imageRenderer->Render(carBodyPosition);

        std::cout << "Rendering car model at position (" << carBodyPosition.x << ", " << carBodyPosition.y << ", " << carBodyPosition.z << ")" << std::endl;
    }

    // ��ȡ����ͼƬ
    std::string GetCarBodyTexture() {
        // ���ø�����Ļ�ȡͼƬ����
        return imageRenderer->GetCarBodyTexture();
    }

    // ��ȡ����ͼƬ
    std::string GetCarDoorTexture() {
        // ���ø�����Ļ�ȡͼƬ����
        return imageRenderer->GetCarDoorTexture();
    }

    // ���Ƴ��ź�ǰ��ǿ��أ����복��״̬����
    void ControlDoors(const std::vector<bool>& doorStates) {
        // ���ø�����Ŀ��Ƴ��ź���
        doorAnimator->AnimateDoors(doorStates);
    }

    // �������ܵĺ���...

private:
    ImageRenderer* imageRenderer; // ͼƬ��Ⱦ������
    DoorAnimator* doorAnimator; // ���Ŷ���������

    // ��Ա����������˽������...
};


���ڣ��������������������ࣺImageRenderer ����ͼƬ��Ⱦ��DoorAnimator ���ڳ��ſ��ض�������������������Ĵ��룺

// ͼƬ��Ⱦ������
class ImageRenderer {
public:
    ImageRenderer() {
        // ��ʼ��ͼƬ��Ⱦ�������
    }

    // ��Ⱦ��ģ�����복��λ�ã����ݳ���λ�ü�������������λ��
    void Render(const glm::vec3& carBodyPosition) {
        // ִ��ͼƬ��Ⱦ���������Ƴ����ͳ��ŵ�
        std::cout << "Rendering car image at position (" << carBodyPosition.x << ", " << carBodyPosition.y << ", " << carBodyPosition.z << ")" << std::endl;
    }

    // ��ȡ����ͼƬ
    std::string GetCarBodyTexture() {
        // ���س���������ļ�·��������
        return "car_body_texture.png";
    }

    // ��ȡ����ͼƬ
    std::string GetCarDoorTexture() {
        // ���س���������ļ�·��������
        return "car_door_texture.png";
    }

    // �������ܵĺ���...
};

// ���Ŷ���������
class DoorAnimator {
public:
    DoorAnimator() {
        // ��ʼ�����Ŷ����������
    }

    // ���Ƴ��ſ��ض��������복��״̬����
    void AnimateDoors(const std::vector<bool>& doorStates) {
        // ִ�г��ſ��ض���
        std::cout << "Animating doors..." << std::endl;
        for (size_t i = 0; i < doorStates.size(); i++) {
            if (doorStates[i]) {
                std::cout << "Door " << i << " is open." << std::endl;
                // ִ�д򿪳��ŵĶ���
            } else {
                std::cout << "Door " << i << " is closed." << std::endl;
                // ִ�йرճ��ŵĶ���
            }
        }
    }

    // �������ܵĺ���...
};



������CarModel ��ֻ��Ҫ����������������ķ�����ʵ��ͼƬ��Ⱦ�ͳ��ſ��ض�����������Ҫ���봦����Щ���ܵľ���ʵ�֡������Ƕ�Ӧ�� UML ��ͼ��


-------------------------------------------
|                CarModel                 |
-------------------------------------------
| - imageRenderer: ImageRenderer*        |
| - doorAnimator: DoorAnimator*          |
-------------------------------------------
| + CarModel(modelName: std::string)     |
| + ~CarModel()                           |
| + Render(carBodyPosition: glm::vec3)   |
| + GetCarBodyTexture()                  |
| + GetCarDoorTexture()                  |
| + ControlDoors(doorStates: std::vector<bool>) |
-------------------------------------------

---------------------------
|     ImageRenderer       |
---------------------------
| - ͼƬ��Ⱦ�������...      |
---------------------------
| + Render(carBodyPosition: glm::vec3)   |
| + GetCarBodyTexture()                  |
| + GetCarDoorTexture()                  |
| + �������ܵĺ���...                 |
---------------------------

---------------------------
|     DoorAnimator        |
---------------------------
| - ���Ŷ����������...      |
---------------------------
| + AnimateDoors(doorStates: std::vector<bool>) |
| + �������ܵĺ���...                 |
---------------------------




������ UML ��ͼ�У�CarModel ������� ImageRenderer �� DoorAnimator �����������ָ�룬��ͨ������������������ķ�����ʵ��ͼƬ��Ⱦ�ͳ��ſ��ض������������ģʽ���� CarModel �ౣ�ּ�࣬ͬʱ�����幦��ί�и�ר�ŵĸ����ദ��


���Ҫͨ���󶨲�ͬ������Texture ID����ʵ�ֳ��ŵĿ���Ч������������չ ImageRenderer ����֧�ֲ�ͬ����״̬�µĲ�ͬ�����������޸ĺ�� ImageRenderer ���ʾ�����룺
#include <iostream>
#include <string>
#include <unordered_map> // ���ڴ洢��ͬ����״̬�µ�����

class ImageRenderer {
public:
    ImageRenderer() {
        // ��ʼ��ͼƬ��Ⱦ�������
        // ����Ĭ�ϳ���ͳ�������
        LoadTextures();
    }

    // ��Ⱦ��ģ�����복��λ�ã����ݳ���λ�ü�������������λ��
    void Render(const glm::vec3& carBodyPosition) {
        // ���ݳ���λ�ü����������������糵�ţ���λ��
        // ִ��ͼƬ��Ⱦ���������Ƴ����ͳ��ŵ�
        std::cout << "Rendering car image at position (" << carBodyPosition.x << ", " << carBodyPosition.y << ", " << carBodyPosition.z << ")" << std::endl;

        // ��Ⱦ���ţ����ݳ���״̬����Ӧ������
        BindDoorTexture(doorStates[0], "front_left_door");
        BindDoorTexture(doorStates[1], "front_right_door");
        BindDoorTexture(doorStates[2], "rear_left_door");
        BindDoorTexture(doorStates[3], "rear_right_door");
    }

    // ��ȡ����ͼƬ
    std::string GetCarBodyTexture() {
        // ���ص�ǰ����������ļ�·��������
        return carBodyTexturePath;
    }

    // ��ȡ����ͼƬ
    std::string GetCarDoorTexture() {
        // ���ص�ǰ����������ļ�·��������
        return carDoorTexturePath;
    }

    // ���ó���״̬
    void SetDoorStates(const std::vector<bool>& states) {
        if (states.size() == NUM_DOORS) {
            doorStates = states;
        }
    }

    // �������ܵĺ���...

private:
    static const int NUM_DOORS = 4; // ������4������

    std::unordered_map<std::string, std::string> textures; // �洢��ͬ����������·��
    std::string carBodyTexturePath;
    std::string carDoorTexturePath;
    std::vector<bool> doorStates; // ����״̬����

    // ����Ĭ�ϳ���ͳ�������
    void LoadTextures() {
        textures["car_body"] = "car_body_texture.png";
        textures["front_left_door"] = "front_left_door_texture.png";
        textures["front_right_door"] = "front_right_door_texture.png";
        textures["rear_left_door"] = "rear_left_door_texture.png";
        textures["rear_right_door"] = "rear_right_door_texture.png";

        carBodyTexturePath = textures["car_body"];
        carDoorTexturePath = textures["front_left_door"]; // ��ʼ��������
    }

    // ���ݳ���״̬����Ӧ������
    void BindDoorTexture(bool isOpen, const std::string& doorName) {
        if (textures.find(doorName) != textures.end()) {
            if (isOpen) {
                // ������Ŵ򿪣��󶨳��Ŵ�״̬������
                carDoorTexturePath = textures[doorName + "_open"];
            } else {
                // ������Źرգ��󶨳��Źر�״̬������
                carDoorTexturePath = textures[doorName + "_closed"];
            }
        }
    }

    // �������ܵ�˽�к���...
};




�����������У�ImageRenderer ��ʹ����һ�� textures ��ϣ�����洢��ͬ����������·������ LoadTextures �����У���ʼ����Ĭ�ϵĳ���ͳ�������BindDoorTexture �������ڸ��ݳ���״̬������Ӧ�ĳ�������������Ŵ򿪣���󶨳��Ŵ�״̬������������Źرգ���󶨳��Źر�״̬������

���ڣ�CarModel �����ʹ�� SetDoorStates ���������ó���״̬��Ȼ��ͨ�� Render ��������Ⱦ��ģ�͡��������������� CarModel ���п��Ƴ���״̬���� ImageRenderer �ฺ����Ⱦ�����������ַ�ʽ��������ʵ�ָ��ݳ���״̬�л������Ч����

�����Ƕ�Ӧ�� UML ��ͼ��


-------------------------------------------
|                CarModel                 |
-------------------------------------------
| - imageRenderer: ImageRenderer*        |
-------------------------------------------
| + CarModel(modelName: std::string)     |
| + ~CarModel()                           |
| + Render(carBodyPosition: glm::vec3)   |
| + GetCarBodyTexture()                  |
| + GetCarDoorTexture()                  |
| + SetDoorStates(states: std::vector<bool>) |
| + �������ܵĺ���...                    |
-------------------------------------------

---------------------------
|     ImageRenderer       |
---------------------------
| - textures: std::unordered_map<std::string, std::string> |
| - carBodyTexturePath: std::string         |
| - carDoorTexturePath: std::string         |
| - doorStates: std::vector<bool>           |
---------------------------
| + ImageRenderer()                       |
| + LoadTextures()                        |
| + Render(carBodyPosition: glm::vec3)    |
| + GetCarBodyTexture()                   |
| + GetCarDoorTexture()                   |
| + SetDoorStates(states: std::vector<bool>) |
| + �������ܵĺ���...                    |
---------------------------
����� UML ��ͼ�У�CarModel ��� ImageRenderer ��֮�佨���˹�����CarModel ����Ե��� ImageRenderer ��ķ�����������������л���



