    for (int row = 0; row < rows; row++) {

        string config = "";
        cout << "Enter intial cells for row " << row + 1 << " [-]dead, [o]alive: "; 
        cin >> config;
        cout << endl;


        for (int column = 0; column < config.length(); column++) {
            if ((config[column] != 'o' && config[column] != '-') || config.length() > 10){
                cout << "Invalid inputs generate a random row." << endl;
                Sleep(1000);
                config = "----------";

                for (int cell = 0; cell < config.length(); cell++) {
                    srand(static_cast<unsigned int>(time(0)));
                    config[cell] = (rand() % 2 == 0 ? 'o' : '-');
                }
            } 

        }