//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2021
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "td/telegram/GroupCallParticipantOrder.h"

#include "td/utils/misc.h"
#include "td/utils/SliceBuilder.h"

#include <limits>
#include <tuple>

namespace td {

GroupCallParticipantOrder GroupCallParticipantOrder::min() {
  return GroupCallParticipantOrder(false, 0, 0, 1);
}

GroupCallParticipantOrder GroupCallParticipantOrder::max() {
  return GroupCallParticipantOrder(true, std::numeric_limits<int32>::max(), std::numeric_limits<int64>::max(),
                                   std::numeric_limits<int32>::max());
}

bool GroupCallParticipantOrder::is_valid() const {
  return *this != GroupCallParticipantOrder();
}

string GroupCallParticipantOrder::get_group_call_participant_order_object() const {
  if (!is_valid()) {
    return string();
  }
  return PSTRING() << (has_video ? '1' : '0') << lpad0(to_string(active_date), 10)
                   << lpad0(to_string(raise_hand_rating), 19) << lpad0(to_string(joined_date), 10);
}

bool operator==(const GroupCallParticipantOrder &lhs, const GroupCallParticipantOrder &rhs) {
  return lhs.has_video == rhs.has_video && lhs.active_date == rhs.active_date && lhs.joined_date == rhs.joined_date &&
         lhs.raise_hand_rating == rhs.raise_hand_rating;
}

bool operator!=(const GroupCallParticipantOrder &lhs, const GroupCallParticipantOrder &rhs) {
  return !(lhs == rhs);
}

bool operator<(const GroupCallParticipantOrder &lhs, const GroupCallParticipantOrder &rhs) {
  auto lhs_has_video = static_cast<int32>(lhs.has_video);
  auto rhs_has_video = static_cast<int32>(rhs.has_video);
  return std::tie(lhs_has_video, lhs.active_date, lhs.raise_hand_rating, lhs.joined_date) <
         std::tie(rhs_has_video, rhs.active_date, rhs.raise_hand_rating, rhs.joined_date);
}

bool operator<=(const GroupCallParticipantOrder &lhs, const GroupCallParticipantOrder &rhs) {
  return !(rhs < lhs);
}

bool operator>(const GroupCallParticipantOrder &lhs, const GroupCallParticipantOrder &rhs) {
  return rhs < lhs;
}

bool operator>=(const GroupCallParticipantOrder &lhs, const GroupCallParticipantOrder &rhs) {
  return !(lhs < rhs);
}

StringBuilder &operator<<(StringBuilder &string_builder,
                          const GroupCallParticipantOrder &group_call_participant_order) {
  return string_builder << group_call_participant_order.has_video << '/' << group_call_participant_order.active_date
                        << '/' << group_call_participant_order.raise_hand_rating << '/'
                        << group_call_participant_order.joined_date;
}

}  // namespace td
