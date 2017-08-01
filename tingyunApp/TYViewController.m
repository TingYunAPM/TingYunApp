//
//  TYViewController.m
//  tingyunApp
//
//  Created by Kang on 2017/8/1.
//  Copyright © 2017年 kang. All rights reserved.
//

#import "TYViewController.h"
#import "NBSAppAgent.h"

@interface TYViewController ()

@end

@implementation TYViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [NBSAppAgent startWithAppID:@"xxx-xxx-xxx"];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
