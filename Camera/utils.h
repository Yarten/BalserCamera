#pragma once


#define PrivateMember(_type_, _name_, _assert_) \
	public: \
		_type_ get##_name_() const { return _name_; } \
		bool set##_name_(const _type_ & _name_) \
		{ \
			if(!(_assert_)) return false; \
			this->_name_ = _name_; \
			return true; \
		} \
	private: \
		_type_ _name_;

#define PrivatePointerMember(_type_, _name_, _assert_) \
	public: \
		_type_ get##_name_() const { return _name_; } \
		bool set##_name_(_type_  _name_) \
		{ \
			if(!(_assert_)) return false; \
			this->_name_ = _name_; \
			return true; \
		} \
	private: \
		_type_ _name_;


#define ProtectedMember(_type_, _name_, _assert_) \
	public: \
		_type_ get##_name_() const { return _name_; } \
		bool set##_name_(const _type_ & _name_) \
		{ \
			if(!(_assert_)) return false; \
			this->_name_ = _name_; \
			return true; \
		} \
	protected: \
		_type_ _name_;