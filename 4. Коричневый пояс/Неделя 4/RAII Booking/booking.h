#include <utility>

namespace RAII {
    template<class Provider>
    class Booking {
        Provider *pProvider;
        int mBookingId;
    public:
        Booking(Provider *provider, int bookingId) : pProvider(std::move(provider)), mBookingId(bookingId) {}

        Booking(Booking &&other) {
            pProvider = std::move(other.pProvider);
            mBookingId = std::move(other.mBookingId);
            other.pProvider = nullptr;
        }

        Booking(const Booking &) = delete;

        ~Booking() {
            if (pProvider) {
                pProvider->CancelOrComplete(*this);
            }
        }

        Booking &operator=(const Booking &) = delete;

        Booking &operator=(Booking &&other) {
            pProvider = std::move(other.pProvider);
            mBookingId = std::move(other.mBookingId);
            other.pProvider = nullptr;
            return *this;
        }
    };
}
