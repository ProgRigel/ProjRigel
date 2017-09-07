//Copyright (c) 2012-2015 ApEk, NoAvailableAlias, Nano-signal-slot Contributors
//https://github.com/NoAvailableAlias/nano-signal-slot/
//
#pragma once
#include <array>
#include <cstdint>

namespace rg {

	using DelegateKey = std::array<std::uintptr_t, 2>;

	template <typename RT> class Function;
	template <typename RT, typename... Args>
	class Function<RT(Args...)>
	{
		using Thunk = RT(*)(void*, Args...);

		friend class Observer;

		void* m_this_ptr; // instance pointer
		Thunk m_stub_ptr; // free function pointer

		Function(void* this_ptr, Thunk stub_ptr) :
			m_this_ptr(this_ptr), m_stub_ptr(stub_ptr) {}

		Function(DelegateKey delegate_key) :
			m_this_ptr(reinterpret_cast<void*>(delegate_key[0])),
			m_stub_ptr(reinterpret_cast<Thunk>(delegate_key[1])) {}

	public:

		template <RT(*fun_ptr) (Args...)>
		static inline Function bind()
		{
			return{ nullptr, [](void* /*NULL*/, Args... args)
			{ return (*fun_ptr)(std::forward<Args>(args)...); } };
		}
		template <typename T, RT(T::* mem_ptr) (Args...)>
		static inline Function bind(T* pointer)
		{
			return{ pointer, [](void* this_ptr, Args... args)
			{ return (static_cast<T*>(this_ptr)->*mem_ptr) (std::forward<Args>(args)...); } };
		}
		template <typename T, RT(T::* mem_ptr) (Args...) const>
		static inline Function bind(T* pointer)
		{
			return{ pointer, [](void* this_ptr, Args... args)
			{ return (static_cast<T*>(this_ptr)->*mem_ptr) (std::forward<Args>(args)...); } };
		}
		template <typename L>
		static inline Function bind(L* pointer)
		{
			return
			{ 
				pointer, 
				[](void *this_ptr, Args... args){ 
				return (static_cast<L*>(this_ptr)->operator()(std::forward<Args>(args)...)); 
				}
			};
		}
		inline operator DelegateKey() const
		{
			return
			{ {
					reinterpret_cast<std::uintptr_t>(m_this_ptr),
					reinterpret_cast<std::uintptr_t>(m_stub_ptr)
				} };
		}
		template <typename... Uref>
		inline RT operator() (Uref&&... args)
		{
			return (*m_stub_ptr)(m_this_ptr, std::forward<Uref>(args)...);
		}
	};

	class Observer
	{

		template <typename T> friend class Signal;

		struct DelegateKeyObserver { DelegateKey delegate; Observer* observer; };
		struct Node { DelegateKeyObserver data; Node* next; } *head = nullptr;

		//-----------------------------------------------------------PRIVATE METHODS

		void insert(DelegateKey const& key, Observer* obs)
		{
			head = new Node{ { key, obs }, head };
		}

		void remove(DelegateKey const& key, Observer* obs)
		{
			Node* node = head;
			Node* prev = nullptr;
			// Only delete the first occurrence
			for (; node; prev = node, node = node->next)
			{
				if (node->data.delegate == key && node->data.observer == obs)
				{
					if (prev)
					{
						prev->next = node->next;
					}
					else
					{
						head = head->next;
					}
					delete node;
					break;
				}
			}
		}

		void removeAll()
		{
			for (auto node = head; node;)
			{
				auto temp = node;
				// If this is us we only need to delete
				if (this != node->data.observer)
				{
					// Remove this slot from this listening Observer
					node->data.observer->remove(node->data.delegate, this);
				}
				node = node->next;
				delete temp;
			}
			head = nullptr;
		}

		bool isEmpty() const
		{
			return head == nullptr;
		}

		template <typename Delegate, typename... Uref>
		void onEach(Uref&&... args)
		{
			for (auto node = head, next = head; node; node = next)
			{
				next = node->next;
				// Perfect forward and emit
				Delegate(node->data.delegate)(std::forward<Uref>(args)...);
			}
		}

		template <typename Delegate, typename Accumulate, typename... Uref>
		void onEach_Accumulate(Accumulate&& accumulate, Uref&&... args)
		{
			for (auto node = head, next = head; node; node = next)
			{
				next = node->next;
				// Perfect forward, emit, and accumulate the return value
				accumulate(Delegate(node->data.delegate)(std::forward<Uref>(args)...));
			}
		}

		//-----------------------------------------------------------------PROTECTED

	protected:

		~Observer()
		{
			removeAll();
		}

		//--------------------------------------------------------------------PUBLIC

	public:

		Observer() = default;
		Observer(const Observer& other) = delete; // non construction-copyable
		Observer& operator=(const Observer&) = delete; // non copyable

	};

	template <typename RT> class Signal;
	template <typename RT, typename... Args>
	class Signal<RT(Args...)> : private Observer
	{
		template <typename T>
		void insert_sfinae(DelegateKey const& key, typename T::Observer* instance)
		{
			Observer::insert(key, instance);
			instance->insert(key, this);
		}
		template <typename T>
		void remove_sfinae(DelegateKey const& key, typename T::Observer* instance)
		{
			Observer::remove(key, instance);
			instance->remove(key, this);
		}
		template <typename T>
		void insert_sfinae(DelegateKey const& key, ...)
		{
			Observer::insert(key, this);
		}
		template <typename T>
		void remove_sfinae(DelegateKey const& key, ...)
		{
			Observer::remove(key, this);
		}

	public:

		using Delegate = Function<RT(Args...)>;

		//-------------------------------------------------------------------CONNECT

		template <typename L>
		void connect(L* instance)
		{
			Observer::insert(Delegate::template bind(instance), this);
		}
		template <typename L>
		void connect(L& instance)
		{
			connect(std::addressof(instance));
		}

		template <RT(*fun_ptr)(Args...)>
		void connect()
		{
			Observer::insert(Delegate::template bind<fun_ptr>(), this);
		}

		template <typename T, RT(T::* mem_ptr)(Args...)>
		void connect(T* instance)
		{
			insert_sfinae<T>(Delegate::template bind<T, mem_ptr>(instance), instance);
		}
		template <typename T, RT(T::* mem_ptr)(Args...) const>
		void connect(T* instance)
		{
			insert_sfinae<T>(Delegate::template bind<T, mem_ptr>(instance), instance);
		}

		template <typename T, RT(T::* mem_ptr)(Args...)>
		void connect(T& instance)
		{
			connect<T, mem_ptr>(std::addressof(instance));
		}
		template <typename T, RT(T::* mem_ptr)(Args...) const>
		void connect(T& instance)
		{
			connect<T, mem_ptr>(std::addressof(instance));
		}

		//----------------------------------------------------------------DISCONNECT

		template <typename L>
		void disconnect(L* instance)
		{
			Observer::remove(Delegate::template bind(instance), this);
		}
		template <typename L>
		void disconnect(L& instance)
		{
			disconnect(std::addressof(instance));
		}

		template <RT(*fun_ptr)(Args...)>
		void disconnect()
		{
			Observer::remove(Delegate::template bind<fun_ptr>(), this);
		}

		template <typename T, RT(T::* mem_ptr)(Args...)>
		void disconnect(T* instance)
		{
			remove_sfinae<T>(Delegate::template bind<T, mem_ptr>(instance), instance);
		}
		template <typename T, RT(T::* mem_ptr)(Args...) const>
		void disconnect(T* instance)
		{
			remove_sfinae<T>(Delegate::template bind<T, mem_ptr>(instance), instance);
		}

		template <typename T, RT(T::* mem_ptr)(Args...)>
		void disconnect(T& instance)
		{
			disconnect<T, mem_ptr>(std::addressof(instance));
		}
		template <typename T, RT(T::* mem_ptr)(Args...) const>
		void disconnect(T& instance)
		{
			disconnect<T, mem_ptr>(std::addressof(instance));
		}

		//----------------------------------------------------EMIT / EMIT ACCUMULATE

#ifdef NANO_USE_DEPRECATED

		/// Will not benefit from perfect forwarding
		/// TODO [[deprecated]] when c++14 is comfortably supported

		void operator() (Args... args)
		{
			emit(std::forward<Args>(args)...);
		}
		template <typename Accumulate>
		void operator() (Args... args, Accumulate&& accumulate)
		{
			emit_accumulate<Accumulate>
				(std::forward<Accumulate>(accumulate), std::forward<Args>(args)...);
		}

#endif

		template <typename... Uref>
		void emit(Uref&&... args)
		{
			Observer::onEach<Delegate>(std::forward<Uref>(args)...);
		}

		template <typename Accumulate, typename... Uref>
		void emit_accumulate(Accumulate&& accumulate, Uref&&... args)
		{
			Observer::onEach_Accumulate<Delegate, Accumulate>
				(std::forward<Accumulate>(accumulate), std::forward<Uref>(args)...);
		}

		//-------------------------------------------------------------------UTILITY

		bool empty() const
		{
			return Observer::isEmpty();
		}

		void removeAll()
		{
			Observer::removeAll();
		}

	};
}