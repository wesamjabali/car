## Autonomous Car
> Github repo for an autonomous car by Mike Findlay, Wesam Jabali

## Goals
1. Make a car that can go to a waypoint
2. Car should avoid obstacles on the way there
3. Car should determine circular path in a room and set waypoint without reversing
4. Car should run away when chased
5. Car should be styled in one of two ways:
   1. Drift
   2. Off-road
      1. If off-road, implement self-balancing with weight sliders and accelerometer

## Materials:

| Part | Cost | Link | Final? |
| :------- | --: | :---- | -- |
| Teensy 4.1 with pins | $38| [Link](https://www.amazon.com/gp/product/B088D3FWR7/ref=ppx_yo_dt_b_asin_title_o01_s01?ie=UTF8&psc=1) | Yes
|Lidar Sensor | $99 | [Link](https://www.dfrobot.com/product-1125.html) | Yes
| Offroad Car | $155| [Link](https://hobbyking.com/en_us/h-king-desert-fox-1-10-4wd-desert-racer-arr.html?queryID=&objectID=71697&indexName=hbk_live_magento_en_us_products) | Yes
| Motor | included | | Yes |
| Servo | included | | Yes |
| Drift Kit car | $100 | [Link](https://hobbyking.com/en_us/blaze-dfr-1-10-scale-carbon-fiber-drift-car-with-unpainted-bodyshell-artr-red.html?queryID=63233cf23278ec76bae500aa6dab2e28&objectID=72108&indexName=hbk_live_magento_en_us_products) | No

## Mathematical Theory
What variables can we control

Turning angle
   For turning, we can write an over simplified equation to determine steering angle. 
     Theta= +/-(Influence*(average distance within x range within x degrees of lidar)) +/- (same as before but with different range of lidar)

   You can divide the lidar into as many sections as you want, as long as they have a variable in the above eq.

   +/- would be for left or right  
   With straight at 0, any obstacles on the left would start influencing the car to drive right by increasing its value as the distance from obstacle gets shorter.

   Influence would be for how intense we want it to affect the steering (right vs front right vs rear right front right would have more influence over rear right unless we're   doing the chasing program)
   Average distance removes erroneous data, and the range makes sure it only uses data within a reasonable range around the car. 
   The lidar will do 360 degrees, and assign data to each degree, so we need to take the data from front +/- 45°and set it as the front dataset and so on.
   With the distance, influence of variable, and +/- you can get the car to steer away from walls and dodge obstacles

Speed
   For speed, do a similar equation as above, but with different influences and ranges. This would determine if it should be slow by walls on the side of the car, or if it      needs to start slowing down because an obstacle infront of the car is becoming closer. Or it needs to go faster because maya is zooming.

   Also might have to do a different sensor for maya detection, but we can use the same formula. Maybe a bluetooth proximity sensor we put on her collar.
