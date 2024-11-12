// App.js
import React from 'react';
import { BrowserRouter as Router, Route, Routes, Link } from 'react-router-dom';
import { useState } from 'react';
import { Lock, Home, Video, Settings, Info, LogIn } from 'lucide-react';

// Navbar Component
const Navbar = () => {
  return (
    <nav className="bg-blue-600 p-4">
      <div className="container mx-auto flex justify-between items-center">
        <Link to="/" className="text-white text-xl font-bold flex items-center">
          <Lock className="mr-2" /> Smart Door
        </Link>
        <div className="flex space-x-4">
          <NavLink to="/" icon={<Home />}>Home</NavLink>
          <NavLink to="/video" icon={<Video />}>Video</NavLink>
          <NavLink to="/settings" icon={<Settings />}>Settings</NavLink>
          <NavLink to="/about" icon={<Info />}>About</NavLink>
          <NavLink to="/signin" icon={<LogIn />}>Sign In</NavLink>
        </div>
      </div>
    </nav>
  );
};

const NavLink = ({ to, children, icon }) => (
  <Link 
    to={to} 
    className="text-white hover:text-blue-200 flex items-center"
  >
    {icon}
    <span className="ml-1">{children}</span>
  </Link>
);

// Start Page Component
const StartPage = () => {
  return (
    <div className="min-h-screen bg-gray-100">
      <div className="container mx-auto px-4 py-8">
        <h1 className="text-4xl font-bold mb-6">Welcome to Smart Door Access</h1>
        <div className="grid md:grid-cols-2 gap-8">
          <div className="bg-white p-6 rounded-lg shadow-lg">
            <h2 className="text-2xl font-bold mb-4">Getting Started</h2>
            <ol className="list-decimal pl-6 space-y-4">
              <li>Create your account to begin managing your smart door</li>
              <li>Connect your smart door device using the provided QR code</li>
              <li>Set up your preferred authentication methods</li>
              <li>Start managing access and monitoring your door</li>
            </ol>
          </div>
          <div className="bg-white p-6 rounded-lg shadow-lg">
            <h2 className="text-2xl font-bold mb-4">Key Features</h2>
            <ul className="space-y-4">
              <li>✓ Real-time video monitoring</li>
              <li>✓ Remote access control</li>
              <li>✓ Digital key management</li>
              <li>✓ Instant notifications</li>
              <li>✓ Access history logging</li>
            </ul>
          </div>
        </div>
      </div>
    </div>
  );
};

// Home Page Component
const HomePage = () => {
  const [doorStatus, setDoorStatus] = useState('Locked');
  
  return (
    <div className="container mx-auto px-4 py-8">
      <div className="grid md:grid-cols-2 gap-8">
        <div className="bg-white p-6 rounded-lg shadow-lg">
          <h2 className="text-2xl font-bold mb-4">Door Status</h2>
          <div className="flex items-center justify-between mb-4">
            <span>Current Status:</span>
            <span className={`font-bold ${doorStatus === 'Locked' ? 'text-green-600' : 'text-red-600'}`}>
              {doorStatus}
            </span>
          </div>
          <button
            onClick={() => setDoorStatus(doorStatus === 'Locked' ? 'Unlocked' : 'Locked')}
            className="w-full bg-blue-600 text-white py-2 rounded hover:bg-blue-700"
          >
            Toggle Lock
          </button>
        </div>
        <div className="bg-white p-6 rounded-lg shadow-lg">
          <h2 className="text-2xl font-bold mb-4">Recent Activity</h2>
          <div className="space-y-2">
            {/* Placeholder for activity feed */}
            <div className="p-2 bg-gray-100 rounded">
              Door unlocked - 2:30 PM
            </div>
            <div className="p-2 bg-gray-100 rounded">
              Motion detected - 2:15 PM
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

// Video Stream Page Component
const VideoStreamPage = () => {
  return (
    <div className="container mx-auto px-4 py-8">
      <h2 className="text-2xl font-bold mb-4">Live Video Feed</h2>
      <div className="bg-gray-800 rounded-lg shadow-lg aspect-video mb-4">
        <div className="flex items-center justify-center h-full">
          <p className="text-white">Video Stream Placeholder</p>
        </div>
      </div>
      <div className="grid grid-cols-2 gap-4">
        <button className="bg-blue-600 text-white py-2 rounded hover:bg-blue-700">
          Take Screenshot
        </button>
        <button className="bg-red-600 text-white py-2 rounded hover:bg-red-700">
          Record Video
        </button>
      </div>
    </div>
  );
};

// Settings Page Component
const SettingsPage = () => {
  return (
    <div className="container mx-auto px-4 py-8">
      <h2 className="text-2xl font-bold mb-6">Settings</h2>
      <div className="bg-white p-6 rounded-lg shadow-lg">
        <div className="space-y-6">
          <div>
            <h3 className="text-lg font-semibold mb-2">Notification Preferences</h3>
            <div className="space-y-2">
              <label className="flex items-center">
                <input type="checkbox" className="mr-2" />
                Door access notifications
              </label>
              <label className="flex items-center">
                <input type="checkbox" className="mr-2" />
                Motion detection alerts
              </label>
            </div>
          </div>
          <div>
            <h3 className="text-lg font-semibold mb-2">Auto-Lock Settings</h3>
            <select className="w-full p-2 border rounded">
              <option>After 30 seconds</option>
              <option>After 1 minute</option>
              <option>After 5 minutes</option>
              <option>Never</option>
            </select>
          </div>
          <button className="bg-blue-600 text-white py-2 px-4 rounded hover:bg-blue-700">
            Save Settings
          </button>
        </div>
      </div>
    </div>
  );
};

// About Page Component
const AboutPage = () => {
  return (
    <div className="container mx-auto px-4 py-8">
      <div className="bg-white p-6 rounded-lg shadow-lg">
        <h2 className="text-2xl font-bold mb-4">About Smart Door Access</h2>
        <div className="space-y-4">
          <p>
            Smart Door Access Management System is a real-time embedded solution designed to address 
            traditional mechanical lock issues. Our system provides a flexible, digital alternative 
            that leverages cutting-edge technology for enhanced security and convenience.
          </p>
          <h3 className="text-xl font-semibold">Key Features:</h3>
          <ul className="list-disc pl-6">
            <li>Real-time processing for instant access control</li>
            <li>Digital key management with sharing capabilities</li>
            <li>RFID and biometric authentication options</li>
            <li>Real-time notifications and monitoring</li>
            <li>Secure and reliable embedded system</li>
          </ul>
          <p>
            Our system integrates various hardware and software components into a cohesive, 
            reliable, and secure solution suitable for modern, connected households.
          </p>
        </div>
      </div>
    </div>
  );
};

// Sign In Page Component
const SignInPage = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    // Add authentication logic here
    console.log('Sign in attempt:', { email, password });
  };

  return (
    <div className="min-h-screen bg-gray-100 flex items-center justify-center">
      <div className="bg-white p-8 rounded-lg shadow-lg max-w-md w-full">
        <h2 className="text-2xl font-bold mb-6 text-center">Sign In</h2>
        <form onSubmit={handleSubmit} className="space-y-4">
          <div>
            <label className="block text-gray-700 mb-2">Email Address</label>
            <input
              type="email"
              value={email}
              onChange={(e) => setEmail(e.target.value)}
              className="w-full p-2 border rounded"
              required
            />
          </div>
          <div>
            <label className="block text-gray-700 mb-2">Password</label>
            <input
              type="password"
              value={password}
              onChange={(e) => setPassword(e.target.value)}
              className="w-full p-2 border rounded"
              required
            />
          </div>
          <button
            type="submit"
            className="w-full bg-blue-600 text-white py-2 rounded hover:bg-blue-700"
          >
            Sign In
          </button>
        </form>
        <div className="mt-4 text-center">
          <a href="#" className="text-blue-600 hover:text-blue-800">
            Forgot password?
          </a>
        </div>
      </div>
    </div>
  );
};

// Main App Component
const App = () => {
  return (
    <Router>
      <div className="min-h-screen bg-gray-100">
        <Navbar />
        <Routes>
          <Route path="/" element={<StartPage />} />
          <Route path="/home" element={<HomePage />} />
          <Route path="/video" element={<VideoStreamPage />} />
          <Route path="/settings" element={<SettingsPage />} />
          <Route path="/about" element={<AboutPage />} />
          <Route path="/signin" element={<SignInPage />} />
        </Routes>
      </div>
    </Router>
  );
};

export default App;