# Integer rust like function status

Note this table does not include functions implemented ztd::integer that are not in rust.

| Function                        | Implemented        | Notes
| ------------------------------- | ------------------ | -----
| abs                             | Yes                |
| abs_diff                        | Yes                |
| borrowing_sub                   | No                 |
| carrying_add                    | No                 |
| carrying_mul                    | No                 |
| carrying_mul_add                | No                 |
| cast_signed                     | Yes                |
| cast_unsigned                   | Yes                |
| checked_abs                     | Yes                |
| checked_add                     | Yes                |
| checked_add_signed              | Yes - Overload     |
| checked_add_unsigned            | Yes - Overload     |
| checked_div                     | Yes                |
| checked_div_euclid              | Yes                |
| checked_ilog                    | No                 |
| checked_ilog2                   | No                 |
| checked_ilog10                  | No                 |
| checked_isqrt                   | No                 |
| checked_mul                     | Yes                |
| checked_neg                     | Yes                |
| checked_next_multiple_of        | Yes                |
| checked_next_power_of_two       | Yes                |
| checked_pow                     | Yes                |
| checked_rem                     | Yes                |
| checked_rem_euclid              | Yes                |
| checked_shl                     | No                 |
| checked_shr                     | No                 |
| checked_sub                     | Yes                |
| checked_sub_signed              | Yes - Overload     |
| checked_sub_unsigned            | Yes - Overload     |
| count_ones                      | No                 |
| count_zeros                     | No                 |
| div_ceil                        | Yes                |
| div_euclid                      | Yes                |
| div_floor                       | Yes                |
| from_be                         | No                 |
| from_be_bytes                   | No                 |
| from_le                         | No                 |
| from_le_bytes                   | No                 |
| from_ne_bytes                   | No                 |
| ilog                            | No                 |
| ilog2                           | No                 |
| ilog10                          | No                 |
| is_multiple_of                  | No                 |
| is_negative                     | Yes                |
| is_positive                     | Yes                |
| is_power_of_two                 | Yes                |
| isqrt                           | No                 |
| leading_ones                    | No                 |
| leading_zeros                   | No                 |
| midpoint                        | No                 |
| next_multiple_of                | Yes                |
| next_power_of_two               | Yes                |
| overflowing_abs                 | Yes                |
| overflowing_add                 | Yes                |
| overflowing_add_signed          | Yes - Overload     |
| overflowing_add_unsigned        | Yes - Overload     |
| overflowing_div                 | Yes                |
| overflowing_div_euclid          | Yes                |
| overflowing_mul                 | Yes                |
| overflowing_neg                 | Yes                |
| overflowing_pow                 | Yes                |
| overflowing_rem                 | Yes                |
| overflowing_rem_euclid          | Yes                |
| overflowing_shl                 | No                 |
| overflowing_shr                 | No                 |
| overflowing_sub                 | Yes                |
| overflowing_sub_signed          | Yes - Overload     |
| overflowing_sub_unsigned        | Yes - Overload     |
| pow                             | Yes                |
| rem_euclid                      | Yes                |
| reverse_bits                    | No                 |
| rotate_left                     | No                 |
| rotate_right                    | No                 |
| saturating_abs                  | Yes                |
| saturating_add                  | Yes                |
| saturating_add_signed           | No                 | std::add_sat requires both args are the same type
| saturating_add_unsigned         | No                 | std::add_sat requires both args are the same type
| saturating_div                  | Yes                |
| saturating_mul                  | Yes                |
| saturating_neg                  | Yes                |
| saturating_pow                  | Yes                |
| saturating_sub                  | Yes                |
| saturating_sub_signed           | No                 | std::sub_sat requires both args are the same type
| saturating_sub_unsigned         | No                 | std::sub_sat requires both args are the same type
| signum                          | Yes                |
| strict_abs                      | Yes                |
| strict_add                      | Yes                |
| strict_add_signed               | Yes - Overload     |
| strict_add_unsigned             | Yes - Overload     |
| strict_div                      | Yes                |
| strict_div_euclid               | Yes                |
| strict_mul                      | Yes                |
| strict_neg                      | Yes                |
| strict_pow                      | Yes                |
| strict_rem                      | Yes                |
| strict_rem_euclid               | Yes                |
| strict_shl                      | No                 |
| strict_shr                      | No                 |
| strict_sub                      | Yes                |
| strict_sub_signed               | Yes - Overload     |
| strict_sub_unsigned             | Yes - Overload     |
| swap_bytes                      | No                 |
| to_be                           | No                 |
| to_be_bytes                     | No                 |
| to_le                           | No                 |
| to_le_bytes                     | No                 |
| to_ne_bytes                     | No                 |
| trailing_ones                   | No                 |
| trailing_zeros                  | No                 |
| unbounded_shl                   | No                 |
| unbounded_shr                   | No                 |
| unchecked_add                   | No                 |
| unchecked_mul                   | No                 |
| unchecked_neg                   | No                 |
| unchecked_shl                   | No                 |
| unchecked_shr                   | No                 |
| unchecked_sub                   | No                 |
| unsigned_abs                    | Yes                |
| widening_mul                    | No                 |
| wrapping_abs                    | Yes                |
| wrapping_add                    | Yes                |
| wrapping_add_signed             | Yes - Overload     |
| wrapping_add_unsigned           | Yes - Overload     |
| wrapping_div                    | Yes                |
| wrapping_div_euclid             | Yes                |
| wrapping_mul                    | Yes                |
| wrapping_neg                    | Yes                |
| wrapping_next_power_of_two      | Yes                |
| wrapping_pow                    | Yes                |
| wrapping_rem                    | Yes                |
| wrapping_rem_euclid             | Yes                |
| wrapping_shl                    | No                 |
| wrapping_shr                    | No                 |
| wrapping_sub                    | Yes                |
| wrapping_sub_signed             | Yes - Overload     |
| wrapping_sub_unsigned           | Yes - Overload     |
