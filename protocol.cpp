/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <stdlib.h>

#define COMMAND(c) if (is_command_type(c))
#define ARG(n) curr_command.argv[n]
#define OUTPUT(msg...) \
{ int i = strlen(output); sprintf(output+i,msg); }

void interpret_command(char * comm, char * output) {

    parse_command(comm);

    output[0] = 0; // initialize the output at 0

    COMMAND("test-ticks"){
        check_parameter(1);
        int delay = atoi(ARG(1));
        int i;
        for(i=0;i<delay;i++){
            if(i%2==0){
                OUTPUT("tic \n");
            }else{
                OUTPUT("tac \n");
            }
            sleep_ms(1000);
        }
    }

    /************************************************************************
     * AX12
     **********************************************************************/
#ifdef PROTO_HAS_AX12

    COMMAND("set-ax12"){
        check_parameter(4);
        int id = atoi(ARG(1));
        int angle = atoi(ARG(2));
        int speed = atoi(ARG(3));
        int torque = atoi(ARG(4));
        OUTPUT("set id %d angle %d speed %d torque %d\n",id,angle,speed,torque);
        ax12_set_servo(id, angle,speed,torque,AX12_RW_AFAP);
    }

    COMMAND("print-ax12"){
        check_parameter(0);
        ax12_print();
    }

#endif

    /************************************************************************
     * GYRO
     **********************************************************************/
#ifdef TOP_LED
    COMMAND("gyro-on"){
        set_digital_output(TOP_LED,1);
    }

    COMMAND("gyro-off"){
        set_digital_output(TOP_LED,0);
    }
#endif
    /************************************************************************
     * COMPAS
     **********************************************************************/
#ifdef MAGNETIC_SENSOR
    COMMAND("disable-compas"){
        disable_sensor(MAGNETIC_SENSOR);
    }
    /***************************************************************************/

    COMMAND("enable-compas"){
        enable_sensor(MAGNETIC_SENSOR);
    }

    /***************************************************************************/

    COMMAND("read-compas"){
        check_parameter(1);
        int length = atoi(ARG(1));
        if((length>=0)&&(length<=I2C_MAX_LENGTH)){
            char * buf;
            receive_i2c_sensor(MAGNETIC_SENSOR, length, buf);
            sleep_ms(1000);
            int i;
            for(i=0;i<length;i++){
                OUTPUT("%#x ",buf[i]);
            }
        }
    }

    /***************************************************************************/

    COMMAND("calibrate-compas"){
        check_parameter(1);
        int crate = atoi(ARG(1));
        if (crate>0)
            calibrate_compas(crate);
    }

    /***************************************************************************/

    COMMAND("send-compas"){
        int length = atoi(ARG(1));
        if((length>=0)&&(length<=I2C_MAX_LENGTH)){
            check_parameter(length+1);
            char args[I2C_MAX_LENGTH];
            int i;
            for(i=0;i<length;i++)
                args[i] = hex_to_int(ARG(i+2));
            send_i2c_sensor(MAGNETIC_SENSOR,length,args);
        }
    }

    /***************************************************************************/

    COMMAND("send-compas-eeprom"){
        check_parameter(1);
        char args[3];
        args[0]= BOUSSOLE_WRITE_EEPROM;
        args[1] = BOUSSOLE_EEPROM_REGISTER;
        args[2] = hex_to_int(ARG(1));
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("read-compas-eeprom-op"){
        check_parameter(0);
        char args[2];
        args[0]= BOUSSOLE_READ_EEPROM;
        args[1] = BOUSSOLE_EEPROM_REGISTER;
        send_i2c_sensor(MAGNETIC_SENSOR,2,args);
        sleep_ms(100);
        char buf[I2C_MAX_LENGTH];
        receive_i2c_sensor(MAGNETIC_SENSOR, 1, buf);
        sleep_ms(100);
        OUTPUT("%#x ", buf[0]);
    }

    /***************************************************************************/

    COMMAND("read-compas-eeprom"){
        check_parameter(1);
        char args[2];
        args[0]= BOUSSOLE_READ_EEPROM;
        args[1] = hex_to_int(ARG(1));
        send_i2c_sensor(MAGNETIC_SENSOR,2,args);
        sleep_ms(100);
        char buf[I2C_MAX_LENGTH];
        receive_i2c_sensor(MAGNETIC_SENSOR, 1, buf);
        sleep_ms(100);
        OUTPUT("%#x ",buf[0]);
    }

    /***************************************************************************/

    COMMAND("send-compas-ram"){
        check_parameter(1);
        char args[3];
        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_RAM_REGISTER;
        args[2] = hex_to_int(ARG(1));
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("send-compas-ram"){
        check_parameter(1);
        char args[3];
        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_RAM_REGISTER;
        args[2] = hex_to_int(ARG(1));
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("compas-output-mode"){
        check_parameter(1);
        char args[3];
        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
        args[2] = hex_to_int(ARG(1));
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("compas-heading"){
        check_parameter(0);
        char args[3];
        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
        args[2] = 0x00;
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("compas-raw-x"){
        check_parameter(0);
        char args[3];
        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
        args[2] = 0x01;
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("mesure") {
        check_parameter (4);

        int time = atoi(ARG(2));
        int step = atoi(ARG(3));
        int i;
        double v1, v2, v3;
        char args[3];
        unsigned short val;

        Serie X = Serie(2);

        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
        args[2] = atoi(ARG(1));
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);

        //  set_speed_mode(SELF_ROT_TRIGO);
        set_wheel_pwms(1663, 1640);
        sleep_ms(200);

        i=0;
        while (i<time/step) {
            v1 = get_sensor_value(MAGNETIC_SENSOR);

            /*
               args[0]= BOUSSOLE_WRITE_RAM;
               args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
               args[2] = 1;
               send_i2c_sensor(MAGNETIC_SENSOR,3,args);
               sleep_ms(10);
               v2 = get_sensor_value(MAGNETIC_SENSOR);

               args[0]= BOUSSOLE_WRITE_RAM;
               args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
               args[2] = 2;
               send_i2c_sensor(MAGNETIC_SENSOR,3,args);
               sleep_ms(10);
               v3 = get_sensor_value(MAGNETIC_SENSOR);
               */

            printf("%f\n", v1);
            X.push(i, v1, v2, v3);
            sleep_ms(step);
            i++;
        }

        set_speed_mode(STOP_SPEED);
        X.save(ARG(4));

    }

    /***************************************************************************/

    COMMAND("compas-raw-y"){
        check_parameter(0);
        char args[3];
        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
        args[2] = 0x02;
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("compas-x"){
        check_parameter(0);
        char args[3];
        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
        args[2] = 0x03;
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("compas-y"){
        check_parameter(0);
        char args[3];
        args[0]= BOUSSOLE_WRITE_RAM;
        args[1] = BOUSSOLE_OUTPUT_MODE_REGISTER;
        args[2] = 0x04;
        send_i2c_sensor(MAGNETIC_SENSOR,3,args);
    }

    /***************************************************************************/

    COMMAND("compas-saveopmode"){
        check_parameter(0);
        char args[1];
        args[0]= BOUSSOLE_SAVE_TO_EEPROM;
        send_i2c_sensor(MAGNETIC_SENSOR,1,args);
    }

    /***************************************************************************/

    COMMAND("read-compas-ram"){
        check_parameter(0);
        char args[2];
        args[0]= BOUSSOLE_READ_RAM;
        args[1] = BOUSSOLE_RAM_REGISTER;
        send_i2c_sensor(MAGNETIC_SENSOR,2,args);
        sleep_ms(100);
        char buf[I2C_MAX_LENGTH];
        receive_i2c_sensor(MAGNETIC_SENSOR, 1, buf);
        sleep_ms(100);
        OUTPUT("%#x ",buf[0]);
    }


    /***************************************************************************/

    COMMAND("compas") {
        check_parameter(0);
        OUTPUT("%f", magnetic_sensor());
    }

    /***************************************************************************/

    COMMAND("learn-compas-estimator") {
        check_parameter(2);
        int samples = atoi(ARG(1));
        int crate = atoi(ARG(2));
        learn_compas_estimator(samples,crate);
    }

    /***************************************************************************/

    COMMAND("compas-var") {
        check_parameter(1);
        int val = atoi(ARG(1));
        OUTPUT("%f", magnetic_sensor_variation(val));
    }
    /***************************************************************************/

    COMMAND("compas-der") {
        check_parameter(1);
        int val = atoi(ARG(1));
        OUTPUT("%f", get_sensor_derivative(MAGNETIC_SENSOR,val));
    }

    /***************************************************************************/

    COMMAND("compas-queue"){
        check_parameter(1);
        int i;
        int val = atoi(ARG(1));
        while((val--) >0){
            for(i=0;i<SENSOR_QUEUE_LENGTH;i++){
                OUTPUT("%d ",(unsigned int) get_nth_raw_sensor_value(MAGNETIC_SENSOR,i));
            }
            OUTPUT("\n\n");
            sleep_ms(1000);
        }
    }
#endif

    /***************************************************************************/

    COMMAND("self-rot-trigo") {
        check_parameter(0);
        set_speed_mode(SELF_ROT_TRIGO);
    }

    COMMAND("self-rot-anti") {
        check_parameter(0);
        set_speed_mode(SELF_ROT_ANTI);
    }

    /***************************************************************************/

    COMMAND("high") {
        check_parameter(1);
        int delay = atoi(ARG(1));
        set_speed_mode(HIGH_SPEED);
        sleep_ms(delay);
        set_speed_mode(STOP_SPEED);
    }

    /***************************************************************************/

    COMMAND("med") {
        check_parameter(1);
        int delay = atoi(ARG(1));
        set_speed_mode(MEDIUM_SPEED);
        sleep_ms(delay);
        set_speed_mode(STOP_SPEED);
    }

    /***************************************************************************/
    /***************************************************************************/

    COMMAND("low") {
        check_parameter(1);
        int delay = atoi(ARG(1));
        set_speed_mode(LOW_SPEED);
        sleep_ms(delay);
        set_speed_mode(STOP_SPEED);
    }

    /***************************************************************************/

    /***************************************************************************/

    COMMAND("rear") {
        check_parameter(1);
        int delay = atoi(ARG(1));
        set_speed_mode(REAR_SPEED);
        sleep_ms(delay);
        set_speed_mode(STOP_SPEED);
    }

    /***************************************************************************/

    /***************************************************************************/

    COMMAND("trigo") {
        check_parameter(1);
        int delay = atoi(ARG(1));
        set_speed_mode(SELF_ROT_TRIGO);
        sleep_ms(delay);
        set_speed_mode(STOP_SPEED);
    }
    /***************************************************************************/
    COMMAND("antrigo") {
        check_parameter(1);
        int delay = atoi(ARG(1));
        set_speed_mode(SELF_ROT_ANTI);
        sleep_ms(delay);
        set_speed_mode(STOP_SPEED);
    }

    /***************************************************************************/

    COMMAND("stop") {
        check_parameter(0);
        set_speed_mode(STOP_SPEED);
    }

    /***************************************************************************/

    COMMAND("") {
        check_parameter(0);
        set_speed_mode(STOP_SPEED);
    }

#ifdef MAGNETIC_SENSOR
    COMMAND("learn-rwheel") {
        check_parameter(0);
        linear_map lmap;
        learn_right_wheel(&lmap,20);
        int i=0;
        for(i=0;i<20;i++)
            OUTPUT("ang_speed %f cyc_rate %f\n",lmap.x[i],lmap.y[i] );
    }
#endif

    /***************************************************************************/
#ifdef MAGNETIC_SENSOR
    COMMAND("get-ang-speed") {
        check_parameter(1);
        int val = atoi(ARG(1));
        OUTPUT("%f", get_angular_speed(val));
    }
    /***************************************************************************/

    COMMAND("test-ang-speed") {
        check_parameter(0);
        int i,j;
        for(i=2000;i<3000;i+=20){
            OUTPUT("\ncrate %d ang speed %f\n\n", i, right_rate_to_angle_speed((double) i));
            for(j=0;j<SENSOR_QUEUE_LENGTH;j++){
                OUTPUT("%d ",(unsigned int) get_nth_raw_sensor_value(MAGNETIC_SENSOR,j));
            }
            OUTPUT("\n\n");
        }
    }
#endif

    /***************************************************************************/
#ifdef DISTANCE_SENSOR
    COMMAND("dist") {
        check_parameter(0);
        OUTPUT("%f", get_sensor_value(DISTANCE_SENSOR));
    }
#endif
    /***************************************************************************/
#ifdef BUZZER
    COMMAND("set-buz") {
        check_parameter(1);
        int val = atoi(ARG(1));
        set_digital_output(BUZZER, val);
    }

    /***************************************************************************/

    COMMAND("bip-bip") {
        check_parameter(2);
        int time = atoi(ARG(1));
        int period = atoi(ARG(2));
        int i = 0;
        int n;
        int turn_nb = 2 * time / period;
        for (n=0; n<turn_nb; n++) {
            i = 1-i;
            set_digital_output(BUZZER, i);
            sleep_ms(period/2);
        }
        set_digital_output(BUZZER, 0);
    }

#endif
    /***************************************************************************/
#ifdef MOTOR_POWER
    COMMAND("motor-on") {
        check_parameter(0);
        set_digital_output(MOTOR_POWER, 1);
    }

    /***************************************************************************/

    COMMAND("motor-off") {
        check_parameter(0);
        set_digital_output(MOTOR_POWER, 0);
    }
#endif
    /***************************************************************************/




    /***************************************************************************/

    COMMAND("go-ahead") {
        check_parameter(2);
        int mode = atoi(ARG(1));
        int time = atoi(ARG(2));

        if (mode < 0 || mode > 3) OUTPUT("Speed mode in [0,3]");

        OUTPUT("mode %d [%d milliseconds]", mode, time);
        set_speed_mode(mode);
        sleep_ms(time);
        set_speed_mode(STOP_SPEED);

    }

    /***************************************************************************/
#ifdef MAGNETIC_SENSOR
    COMMAND("go-to-cap") {
        check_parameter(1);
        int cap = atoi(ARG(1));
        go_to_cap(cap);
        OUTPUT("new cap : %0.2f", get_sensor_value(MAGNETIC_SENSOR));
    }
#endif
    /***************************************************************************/
#ifdef MAGNETIC_SENSOR
    COMMAND("set-pwm") {
        check_parameter(3);
        int lpwm = atoi(ARG(1));
        int rpwm = atoi(ARG(2));
        int time = atoi(ARG(3));
        set_wheel_pwms(lpwm, rpwm);
        sleep_ms(time);
        set_wheel_pwms(0,0);
    }

    /***************************************************************************/
    COMMAND("go-straight") {
        check_parameter(1);

        go_straight(2.5,           // gain 
                atoi(ARG(1)),  // time (in ms)
                50,            // refresh period (in ms)
                30);           // max correction
    }
#endif
    /***************************************************************************/
    /*
       COMMAND("calibrate") {
       check_parameter(2);
       int Wheel = atoi(ARG(1));
       double target = atof(ARG(2));

       double result = 
       look_for_low_speed (Wheel,
       2000,      // Max pwm 
       1000,      // Min pwm
       target,
       1.0,       // epsilon
       5,         // max number of dichotomy turns
       500,       // duration of runs  
       1);        // repositionning

       OUTPUT("result = %0.2f", result);
       }
       */
    /***************************************************************************/
    /*
       COMMAND("Wheel-zero") {
       check_parameter(0);
       calibrate_zero_wheel();
       }
       */
    /***************************************************************************/
    /*
       COMMAND("Wheel-forward") {
       check_parameter(0);
       calibrate_forward_wheel();
       }
       */
    /***************************************************************************/
    /*
       COMMAND("measure-Wheel") {
       check_parameter(4);

       tw_current_wheel = atoi(ARG(1));   // the Wheel to test
       int pwm_val = atoi(ARG(2));        // the pwm value to test
       tw_current_time = atoi(ARG(3));    // the time for one test
       int measure_nb = atoi(ARG(4));     // the number of measure

       measure * m = alloc_measure();

       do_measure (m,
       test_wheel,
       (double) pwm_val,
       0,
       measure_nb,
       1000);

       OUTPUT("--------------------\n");
       OUTPUT("mean = %0.2f\nstd dev = %0.2f\n", measure_mean(m), measure_std_dev(m));
       OUTPUT("--------------------\n");

       }
       */
    /***************************************************************************/

    COMMAND("save-config") {
        check_parameter(1);
        if (store_in_file(ARG(1), (ui8*) &bot, sizeof(BotConfig)))
            OUTPUT("Done.");
    }

    /***************************************************************************/

    COMMAND("load-config") {
        check_parameter(1);
        if (read_file(ARG(1), (ui8*) &bot, sizeof(BotConfig)))
            OUTPUT("Done.");
    }

    /***************************************************************************/

}
