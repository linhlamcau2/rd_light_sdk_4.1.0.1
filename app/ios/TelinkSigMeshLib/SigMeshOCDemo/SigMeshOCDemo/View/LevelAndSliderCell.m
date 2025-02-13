/********************************************************************************************************
 * @file     LevelAndSliderCell.m
 *
 * @brief    for TLSR chips
 *
 * @author   Telink, 梁家誌
 * @date     2020/11/24
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/

#import "LevelAndSliderCell.h"

@implementation LevelAndSliderCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
}

- (IBAction)changedValue:(UISlider *)sender {
    if ([self.delegate respondsToSelector:@selector(levelAndSliderCell:didChangedValueWithValue:)]) {
        [self.delegate levelAndSliderCell:self didChangedValueWithValue:sender.value];
    }
}

- (IBAction)clickDelete:(UIButton *)sender {
    if ([self.delegate respondsToSelector:@selector(levelAndSliderCellDidClickedDeleteButton:)]) {
        [self.delegate levelAndSliderCellDidClickedDeleteButton:self];
    }
}

- (IBAction)clickAdd:(UIButton *)sender {
    if ([self.delegate respondsToSelector:@selector(levelAndSliderCellDidClickedAddButton:)]) {
        [self.delegate levelAndSliderCellDidClickedAddButton:self];
    }
}

@end
