#include <avr/io.h>
#include <util/delay.h>

// --- SETTINGS ---
#define FORWARD_SPEED 110
#define RIGHT_TRIM    108
#define TURN_SPEED    150  
#define TURN_90_MS    300  

void init_system() {
    // Set Pins 4, 5, 6, 7 (PORTD) and 8, 9 (PORTB) as Output
    DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
    DDRB |= (1 << DDB0) | (1 << DDB1);

    // --- UPDATED INPUTS ---
    DDRD &= ~((1 << DDD2) | (1 << DDD3)); // Pins 2 & 3 as Input
    DDRB &= ~(1 << DDB4);                 // Pin 12 as Input
    PORTB |= (1 << PORTB4);

    // Timer 0 Fast PWM Configuration
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B = (1 << CS01) | (1 << CS00); 
}

void set_motors(uint8_t left_spd, uint8_t right_spd) {
    OCR0A = left_spd; // Pin 6
    OCR0B = right_spd; // Pin 5
}

void stop_car() {
    set_motors(0, 0);
    PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
    PORTD &= ~((1 << PORTD4) | (1 << PORTD7));
}

void forward() {
    // Left Forward: IN1 High, IN2 Low
    PORTB |= (1 << PORTB1); PORTB &= ~(1 << PORTB0);
    // Right Forward: IN3 High, IN4 Low
    PORTD |= (1 << PORTD7); PORTD &= ~(1 << PORTD4);
    set_motors(FORWARD_SPEED, RIGHT_TRIM);
}

void turn_left_90() {
    // Left BACK: IN1 Low, IN2 High
    PORTB &= ~(1 << PORTB1); PORTB |= (1 << PORTB0);
    // Right FORWARD: IN3 High, IN4 Low
    PORTD |= (1 << PORTD7); PORTD &= ~(1 << PORTD4);
    
    set_motors(TURN_SPEED, TURN_SPEED);
    _delay_ms(TURN_90_MS);
    stop_car();
}

void turn_right_90() {
    // Left FORWARD: IN1 High, IN2 Low
    PORTB |= (1 << PORTB1); PORTB &= ~(1 << PORTB0);
    // Right BACK: IN3 Low, IN4 High
    PORTD &= ~(1 << PORTD7); PORTD |= (1 << PORTD4);
    
    set_motors(TURN_SPEED, TURN_SPEED);
    _delay_ms(TURN_90_MS);
    stop_car();
}

int main(void) {
    init_system();   

    while (1) {
        uint8_t center_detected = !(PIND & (1 << PIND2)); 
        uint8_t right_detected  = !(PIND & (1 << PIND3)); 
        uint8_t left_detected = !(PINB & (1 << PINB4));

        // 1. DEAD END (Only Center) -> Escape Left
        if (center_detected && !left_detected && !right_detected) {
            stop_car();
            _delay_ms(300);
            turn_left_90();
            _delay_ms(300);
        }

        else if (!center_detected && left_detected && !right_detected) {
            stop_car();
            _delay_ms(300);
            turn_right_90();
            _delay_ms(300);
        }

        else if (!center_detected && !left_detected && right_detected) {
            stop_car();
            _delay_ms(300);
            turn_left_90();
            _delay_ms(300);
        }

        else if (center_detected && left_detected && !right_detected) {
            stop_car();
            _delay_ms(300);
            turn_right_90();
            _delay_ms(300);
        }

        else if (center_detected && !left_detected && right_detected) {
            stop_car();
            _delay_ms(300);
            turn_left_90();
            _delay_ms(300);
        }


        else {
            forward();
        } 
    }
}